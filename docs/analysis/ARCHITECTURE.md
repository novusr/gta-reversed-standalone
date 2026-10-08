# Architecture Map: GTA Reversed

This document outlines the architecture of Grand Theft Auto: San Andreas as reimplemented in `gta-reversed`, identifying major subsystems, entry points, core managers, data structures, and cross-system dependencies.

---

## 1. Top-Level Engine & Runtime Architecture

```
┌─────────────────────────────────────────────────────────────────────────────────┐
│                           PLATFORM & APPLICATION LAYER                          │
│     WinMain / SDL3 Window    │   Message Loop / WinPs   │   DirectInput / SDL3   │
└────────────────────────────────────────┬────────────────────────────────────────┘
                                         ▼
┌─────────────────────────────────────────────────────────────────────────────────┐
│                                 APP & GAME LOOP                                 │
│   NOTSA_WinMain (0x748710) ──► RsEventHandler ──► AppEventHandler ──► Idle()     │
│   CGame::Initialise() ───────► CGame::Process() ──► CGame::Shutdown()           │
└──────────────────┬─────────────────────┬──────────────────────┬─────────────────┘
                   │                     │                      │
       ┌───────────▼───────────┐         │          ┌───────────▼───────────┐
       │     WORLD & SCENE     │         │          │     RENDER SYSTEM     │
       │ CWorld (120x120 Grid) │         │          │ CRenderer / PostFX    │
       │ CPools (Entities)     │         │          │ RenderWare Pipelines  │
       └───────────┬───────────┘         │          └───────────▲───────────┘
                   │                     │                      │
       ┌───────────▼───────────┐         │          ┌───────────┴───────────┐
       │     ENTITY SYSTEMS    │         │          │       STREAMING       │
       │ CPed / CVehicle       │         │          │ CStreaming / CdStream │
       │ CObject / CPhysical   │         │          │ CFileLoader / Models  │
       └───────────┬───────────┘         │          └───────────────────────┘
                   │                     │
       ┌───────────▼───────────┐         │          ┌───────────────────────┐
       │     AI & GAMEPLAY     │         │          │      AUDIO ENGINE     │
       │ CTaskManager / Tasks  │◄────────┼─────────►│ AudioEngine / CAE...  │
       │ CEventGroup / Events  │         │          │ DirectSound / OpenAL  │
       │ CTheScripts (SCM VM)  │         │          └───────────────────────┘
       └───────────────────────┘         │
                                         ▼
                               ┌───────────────────┐
                               │ COLLISION/PHYSICS │
                               │ CCollision        │
                               │ cBuoyancy/Handling│
                               └───────────────────┘
```

---

## 2. Subsystem Breakdown

### 2.1 Game Loop & Application Lifecycle
* **Source Files**: `source/app/platform/win/WinMain.cpp`, `source/app/app.cpp`, `source/app/app_game.cpp`, `source/game_sa/Game.cpp`.
* **Important Classes**: `CGame`, `RsGlobalType`.
* **Key Global Variables**:
  * `gGameState` (`StaticRef<int32>(0xC8D4C0)`): Tracks states (`GAME_STATE_INITIAL", `GAME_STATE_LOGO`, `GAME_STATE_PLAYING_LOGO`, `GAME_STATE_TITLE`, `GAME_STATE_PLAYING_INTRO`, `GAME_STATE_FRONTEND`, `GAME_STATE_IDLE`).
  * `RsGlobal` (`StaticRef<RsGlobalType>(0xC17040)`): Skeleton application state (dimensions, window handle, quit flag).
* **Main Entry Points**:
  * `NOTSA_WinMain(HINSTANCE, ...)` (`0x748710`): Application entry, parses command line, creates window, sets sticky keys, enters `MainLoop`.
  * `MainLoop(int)` (`0x7489FB`): Runs message loop and dispatches `rsIDLE` events.
  * `Idle(void*)` (`0x53E920`): Per-frame tick handler; checks timers, invokes `CGame::Process()`, and handles scene presentation.
  * `CGame::Initialise(const char* datFile)` (`0x53BC80`): Multi-stage boot sequencer calling `Init1`, loading `DEFAULT.DAT` and `GTA.DAT`, `Init2`, test scripts, and `Init3`.
  * `CGame::Process()` (`0x53BEE0`): Main game tick. Updates pads, streaming, cutscenes, frontend, time, weather, SCM scripts, physics, population, traffic, weapons, camera, audio.
* **Dependencies**: RenderWare skeleton events, Win32 / SDL3, DirectX 9 device, Audio engine.

### 2.2 World & Spatial Partitioning
* **Source Files**: `source/game_sa/World.cpp`, `source/game_sa/World.h`, `source/game_sa/Sector.h`.
* **Important Classes**: `CWorld`, `CSector`, `CRepeatSector`, `CPtrListSingleLink<CEntity*>`, `CPtrListDoubleLink<CPhysical*>`.
* **Key Global Variables**:
  * `CWorld::ms_aSectors` (`StaticRef<mdarray<CSector, 120, 120>>(0xB7D0B8)`): Spatial hash dividing the 6000x6000m map into 14,400 sectors (50x50m each).
  * `CWorld::ms_aRepeatSectors` (`StaticRef<mdarray<CRepeatSector, 16, 16>>(0xB992B8)`): Coarser 16x16 partition for moving physics entities.
  * `CWorld::ms_listMovingEntityPtrs` (`StaticRef<CPtrListDoubleLink<CPhysical*>>(0xB9ACC8)`): Double-linked list of all moving physical entities.
  * `CWorld::Players` (`StaticRef<CPlayerInfo[2]>(0xB7CD98)`): Player slots (single player and 2-player mode).
* **Key Operations**:
  * `CWorld::Process()`: Ticks all active physical entities, applies movement forces, resolves collisions.
  * `CWorld::ProcessLineOfSight(...)`: Raycast through world sectors against buildings, peds, vehicles, and objects.
  * `CWorld::FindEntitiesInRange(...)`: Sphere-query collecting entities within radius.
* **Dependencies**: `CCollision`, `CPools`, `CEntity`, `CPhysical`.

### 2.3 Entity Hierarchy
* **Inheritance Tree**:
  ```
  CPlaceable (Matrix/Position)
      └── CEntity (Type, Flags, RwObject*, ModelIndex)
            ├── CBuilding (Static geometry)
            ├── CDummy (Map placement placeholder)
            └── CPhysical (Velocity, Forces, Mass, Collision State)
                  ├── CObject (Props, breakable objects)
                  ├── CPed (Peds, Player, Cop, Emergency)
                  └── CVehicle (Automobile, Bike, Boat, Plane, Heli, Train, Trailer, BMX, Quad)
  ```
* **Source Locations**:
  * `source/game_sa/Entity/Placeable.h`
  * `source/game_sa/Entity/Entity.cpp`, `Entity.h`
  * `source/game_sa/Entity/Physical.cpp`, `Physical.h`
  * `source/game_sa/Entity/Ped/Ped.cpp`, `Ped.h`, `PlayerPed.cpp`
  * `source/game_sa/Entity/Vehicle/Vehicle.cpp`, `Vehicle.h`, `Automobile.cpp`
  * `source/game_sa/Entity/Object/Object.cpp`, `Object.h`
* **Core Characteristics**:
  * `CEntity` holds `m_pRwObject` (points to `RpClump*` or `RpAtomic*`).
  * `CPhysical` implements Newtonian rigid-body physics: `m_vecMoveSpeed`, `m_vecTurnSpeed`, `m_fMass`, `m_fTurnMass`, `m_vecForce`, `m_vecTorque`.
  * `CPed` contains `CPedIntelligence*`, `CPedIK*`, `CWanted*`, `CWeapon[13]`, `CPedBoneInfo`.
  * `CVehicle` contains `tHandlingData*`, `CDamageManager`, `CVehicleAudioEntity`, suspension states, gear ratios, wheel contact data.

### 2.4 Task & AI System
* **Source Files**: `source/game_sa/Tasks/**`, `source/game_sa/PedIntelligence.cpp`.
* **Important Classes**: `CTaskManager`, `CTask`, `CTaskSimple`, `CTaskComplex`, `CTaskComplexSequence`.
* **Architecture**: Hierarchical Finite State Machine / Action Tree.
  * Each `CPedIntelligence` owns a `CTaskManager` with primary task trees:
    1. Priority Tasks (`TASK_PRIORITY_PHYSICAL_RESPONSE`, `TASK_PRIORITY_EVENT_RESPONSE_TEMP`, `TASK_PRIORITY_EVENT_RESPONSE_NONTEMP`, `TASK_PRIORITY_PRIMARY`, `TASK_PRIORITY_DEFAULT`).
    2. Secondary Tasks (`TASK_SECONDARY_ATTACK`, `TASK_SECONDARY_DUCK`, `TASK_SECONDARY_SAY`, `TASK_SECONDARY_FACIAL_COMPLEX`, `TASK_SECONDARY_PARTIAL_ANIM`).
  * `CTaskComplex` subclasses break into subtasks until resolving to leaf `CTaskSimple` instances (`CTaskSimpleRunAnim`, `CTaskSimpleStandStill`, `CTaskSimpleCarDrive`, etc.).
  * Over **291 distinct task types** implemented in `source/game_sa/Tasks/TaskTypes/`.

### 2.5 Event System (Stimulus Perception)
* **Source Files**: `source/game_sa/Events/**`, `source/game_sa/EventHandler.cpp`.
* **Important Classes**: `CEvent`, `CEventGroup`, `CEventHandler`, `CEventScanner`.
* **Architecture**: Peds register stimuli (gunshots, damage, sight of cops, car horn, explosions) via `CEvent` objects pushed into the ped's `CEventGroup`.
* `CEventHandler::ComputeResponseTask(...)` evaluates personality, acquaintances (`CAcquaintance`), and threat priorities to generate response tasks (flee, attack, duck, cower).

### 2.6 Population & Traffic Generation
* **Source Files**: `source/game_sa/Population.cpp`, `source/game_sa/PopCycle.cpp`, `source/game_sa/CarCtrl.cpp`, `source/game_sa/TheCarGenerators.cpp`.
* **Important Classes**: `CPopulation`, `CPopCycle`, `CCarCtrl`, `CTheCarGenerators`, `CLoadedCarGroup`.
* **Key Global Variables**:
  * `CPopCycle` loaded from `DATA/POPCYCLE.DAT` defines ped/vehicle densities per zone and hour of day.
  * `CTheCarGenerators` manages static parked vehicles around the world.
  * `CCarCtrl` handles random vehicle cruising, lane changing, intersection stopping, and distant car despawning.

### 2.7 Collision & Geometry
* **Source Files**: `source/game_sa/Collision/Collision.cpp`, `source/game_sa/Collision/ColStore.cpp`, `source/game_sa/Collision/ColModel.cpp`.
* **Important Classes**: `CCollision`, `CColStore`, `CColModel`, `CColData`, `CColSphere`, `CColBox`, `CColLine`, `CColTriangle`, `CColTrianglePlane`.
* **Key Global Variables**:
  * `CCollision::ms_colModelCache`: LRU cache for dynamically unpacked triangle collision planes.
  * `CColStore`: Manages loading and streaming `.col` collision files from disk.
* **Core Functionality**: Primitive testing (`TestSphereSphere`, `TestSphereBox`, `TestLineTriangle`), swept tests, ground height queries (`CWorld::FindGroundZForCoord`), and mesh contact resolution.

### 2.8 Animation System
* **Source Files**: `source/game_sa/Animation/AnimManager.cpp`, `source/game_sa/Animation/RpAnimBlend.cpp`.
* **Important Classes**: `CAnimManager`, `CAnimBlendAssociation`, `CAnimBlendHierarchy`, `CAnimBlock`, `RpAnimBlendClump`.
* **Core Characteristics**:
  * Hierarchical skeletal animation loaded from `.ifp` (Internal Frame Packet) archives.
  * Operates on RenderWare `RpHAnimHierarchy` bone structures.
  * Blends multiple animation tracks simultaneously (e.g. running while shooting while gesturing facial expressions) with weight interpolation and priority flags.

### 2.9 Streaming & Virtual Filesystem
* **Source Files**: `source/game_sa/Streaming.cpp`, `source/game_sa/CdStreamInfo.cpp`, `source/game_sa/FileLoader.cpp`, `source/game_sa/FileMgr.cpp`.
* **Important Classes**: `CStreaming`, `CdStreamInfo`, `CStreamingInfo`, `CFileLoader`, `CFileMgr`.
* **Key Global Variables**:
  * `CStreaming::ms_aInfoForModel` (`StaticRef<CStreamingInfo[26316]>(0x8E4CC0)`): State array for every streamable asset (DFF, TXD, COL, IPL, DAT, IFP, RRR, SCM).
  * `CStreaming::ms_channel` (`StaticRef<tStreamingChannel[2]>(0x8E4C40)`): Two asynchronous streaming I/O channels reading from `.img` archives.
  * `CdStream`: Low-level asynchronous CD/disk archive reader.
* **Operation**:
  * `CStreaming::RequestModel(...)` queues asset requests based on player position, camera frustum, and script needs.
  * `CStreaming::Update()` services I/O channels, reads blocks into memory buffers, and calls `CStreaming::ConvertBufferToObject` to construct RenderWare clumps/textures.

### 2.10 Rendering & RenderWare Integration
* **Source Files**: `source/game_sa/Renderer.cpp`, `source/game_sa/VisibilityPlugins.cpp`, `source/game_sa/RenderWare/rw/**`, `source/game_sa/Pipelines/**`.
* **Important Classes**: `CRenderer`, `CVisibilityPlugins`, `CCarFXRenderer`, `CCustomBuildingRenderer`, `CPostEffects`, `CShadows`, `CRealTimeShadowManager`.
* **Render Loop Sequence (`CRenderer::RenderRoads`, `CRenderer::RenderEverythingBarRoads`)**:
  1. Camera setup and frustum cull calculation (`CVisibilityPlugins::SetRenderWareCamera`).
  2. Sorting entities into opaque, translucent, alpha-tested, and underwater buckets.
  3. Directional and ambient lighting updates (`SetLightsWithTimeOfDayColour`).
  4. Dispatching `RpAtomicRender` / `RpClumpRender` through custom D3D9 vertex pipelines (`CustomBuildingDNPipeline`, `CustomCarEnvMapPipeline`).
  5. Rendering 2D effects, glass, water surfaces, clouds, and post-processing passes.

### 2.11 Audio System
* **Source Files**: `source/game_sa/Audio/**`.
* **Important Classes**: `CAudioEngine` (`AudioEngine`), `CAEAudioHardware`, `CAESoundManager`, `CAEVehicleAudioEntity`, `CAEPedAudioEntity`, `CAEAmbienceTrackManager`, `CAERadioTrackManager`.
* **Dual Backend**: Supports DirectSound (`USE_DSOUND`) or OpenAL (`USE_OPENAL`, `source/game_sa/Audio/OpenAL/`).
* **Functionality**: Multi-channel 3D positional audio, vehicle engine RPM acoustic synthesis, Doppler shifting, occlusion attenuation, radio station streaming (Ogg Vorbis / ADPCM), ambient world soundscapes, and scripted character dialogue.

### 2.12 Mission Scripting (SCM Engine)
* **Source Files**: `source/game_sa/Scripts/TheScripts.cpp`, `source/game_sa/Scripts/RunningScript.cpp`, `source/game_sa/Scripts/Commands/**`.
* **Important Classes**: `CTheScripts`, `CRunningScript`.
* **Key Global Variables**:
  * `CTheScripts::ScriptSpace` (`StaticRef<array<uint8, 251200>>(0xA49960)`): Holds loaded `main.scm` bytecode and mission scripts.
  * `CTheScripts::ScriptsArray` (`StaticRef<array<CRunningScript, 96>>(0xA8B430)`): Active running script threads.
* **Architecture**: Virtual machine interpreting bytecode instructions (opcodes `0000` through `0A4E`), managing global script variables, thread timers, script text, blips, cutscenes, mission logic, and subroutines.

### 2.13 Memory Management & Object Pools
* **Source Files**: `source/game_sa/MemoryMgr.cpp`, `source/game_sa/Pools/Pools.cpp`, `source/game_sa/Core/Pool.h`.
* **Important Classes**: `CMemoryMgr`, `CPools`, `CPool<T, S>`.
* **Pool Allocations**:
  * Peds: `CPedPool` (capacity 140)
  * Vehicles: `CVehiclePool` (capacity 110)
  * Buildings: `CBuildingPool` (capacity 13,000)
  * Objects: `CObjectPool` (capacity 350)
  * Dummy entities: `CDummyPool` (capacity 2,500)
  * ColModels: `CColModelPool` (capacity 10,150)
  * Tasks: `CTaskPool` (capacity 500)
  * Events: `CEventPool` (capacity 200)
* Fixed-size pre-allocated slotted arrays with generation/ref counting to prevent stale pointer access.
