# Architecture: GTA Reversed Standalone Target

This document establishes the architectural foundation of `gta-reversed` and defines the target standalone architecture for evolving it from an injected ASI into an independent, native C++ GTA San Andreas runtime.

---

## 1. Architectural Philosophy & Core Tenets

1. **Evolutionary Migration, Not a New Engine**:
   The objective is to preserve the existing reverse-engineered GTA San Andreas gameplay and engine logic (over 408,000 lines across hundreds of classes). The codebase is NOT to be rewritten into an Entity-Component-System (ECS), a clean-room clone, or a modernized engine framework.
2. **Dual-Mode Coexistence**:
   The existing ASI injection mode (`gta_reversed.asi`) remains intact as a behavioral reference and verification target against vanilla `gta_sa.exe`. Standalone mode (`gta_reversed.exe` / native executable) builds alongside it.
3. **Preservation of Class Hierarchy & Memory Layout**:
   The proven object-oriented hierarchy:
   ```text
   CPlaceable
     └── CEntity
           ├── CBuilding
           ├── CDummy
           └── CPhysical
                 ├── CObject
                 ├── CPed
                 │    └── CPlayerPed
                 └── CVehicle
                       ├── CAutomobile
                       ├── CBike
                       ├── CBoat
                       ├── CPlane
                       ├── CHeli
                       ├── CTrain
                       └── CQuad
   ```
   is tightly coupled to physics formulas, animation skeletons, collision algorithms, and SCM bytecode opcodes. This hierarchy must be strictly preserved.
4. **Behavioral Fidelity Over Modernization**:
   Gameplay formulas, vehicle handling mathematics, AI task trees (291 task types), event handlers (83 event types), script opcodes (800+ opcodes), and world sector hashing must function identically to the original game.

---

## 2. High-Level System Architecture

```text
┌─────────────────────────────────────────────────────────────────────────────────┐
│                           PLATFORM ABSTRACTION LAYER                            │
│    SDL3 (Windowing, Input Events, Display)  │  OpenAL-Soft (3D Positional Audio)│
│    VFS / CFileMgr (Normalized Paths, Case-Insensitive Lookup, IMG Archive Mnt)  │
└────────────────────────────────────────┬────────────────────────────────────────┘
                                         ▼
┌─────────────────────────────────────────────────────────────────────────────────┐
│                                ENGINE CORE RUNTIME                              │
│    librw (RenderWare 3.x API: Rasters, Clumps, Atomics, Textures, Custom Pipes) │
│    Native Memory Management (Native C++ new/delete, CPool Allocators)           │
│    High-Resolution Timer (std::chrono Frame Ticking, Game Timer)                │
└────────────────────────────────────────┬────────────────────────────────────────┘
                                         ▼
┌─────────────────────────────────────────────────────────────────────────────────┐
│                            ASSET & STREAMING ENGINE                             │
│    CdStream (Async Archive I/O for gta3.img, gta_int.img)                       │
│    CFileLoader (Parsing IDE, IPL, DAT, COL, IFP, TXD, DFF)                      │
│    CStreaming (Priority Queue, Memory Budget Enforcement, LRU Model Cache)      │
└────────────────────────────────────────┬────────────────────────────────────────┘
                                         ▼
┌─────────────────────────────────────────────────────────────────────────────────┐
│                          SIMULATION & GAMEPLAY RUNTIME                          │
│                                                                                 │
│   ┌─────────────────────┐  ┌─────────────────────┐  ┌───────────────────────┐   │
│   │    WORLD & SCENE    │  │   ENTITY HIERARCHY  │  │     AI & BEHAVIOR     │   │
│   │ CWorld (120x120)    │  │ CPed, CPlayerPed    │  │ CTaskManager (291 T)  │   │
│   │ Spatial Hash / Casts│  │ CVehicle, CObject   │  │ CEventHandler (83 E)  │   │
│   └──────────┬──────────┘  └──────────┬──────────┘  └───────────┬───────────┘   │
│              │                        │                         │               │
│   ┌──────────┴──────────┐  ┌──────────┴──────────┐  ┌───────────┴───────────┐   │
│   │  COLLISION/PHYSICS  │  │    MISSION & SCM    │  │   MANAGERS & CONTROL  │   │
│   │ CCollision, ColStore│  │ CTheScripts (VM)    │  │ CPopulation, CWanted  │   │
│   │ cHandlingDataMgr    │  │ 800+ Script Opcodes │  │ CCarCtrl, CRadar, HUD │   │
│   └─────────────────────┘  └─────────────────────┘  └───────────────────────┘   │
└─────────────────────────────────────────────────────────────────────────────────┘
```

---

## 3. Subsystem Architecture & Responsibilities

### 3.1 Application Lifecycle & Main Loop
* **ASI Entry**: `DllMain` (`source/dllmain.cpp`) hooks GTA.exe entry points (`0x748710`, `0x53E920`, etc.).
* **Standalone Entry**: `Main.cpp` / `WinMain.cpp` boots the native runtime.
* **Game Lifecycle**:
  ```text
  Boot (WinMain / main)
    ↓
  Platform Init (SDL3 window, input, audio device)
    ↓
  Engine Init (CGame::InitialiseOnceBeforeRW -> RenderWare/librw -> CGame::Initialise)
    ↓
  Game Loop (Idle -> CGame::Process -> Render -> Present)
    ↓
  Shutdown (CGame::Shutdown -> Engine Cleanup -> Platform Teardown)
  ```
* **Per-Frame Tick (`CGame::Process()`)**:
  1. Input polling (`CPad::UpdatePads()`).
  2. Audio tick (`AudioEngine.Service()`).
  3. Timer update (`CTimer::Update()`).
  4. Script processing (`CTheScripts::Process()`).
  5. World physics and entity tick (`CWorld::Process()`).
  6. AI task execution (`CTaskManager::ManageTasks()`).
  7. Traffic and population updates (`CCarCtrl::PruneStuff()`, `CPopulation::Update()`).
  8. Streaming tick (`CStreaming::Update()`).

### 3.2 Dual-Mode State Model (`StaticRef` Abstraction)
* **Problem**: In ASI mode, globals reside at fixed virtual memory addresses in `gta_sa.exe` (e.g., `0xB74490` for `CPedPool*`).
* **Standalone Strategy**:
  ```cpp
  #ifdef NOTSA_STANDALONE_NATIVE
      // Native static member storage or standalone state registry
      #define NOTSA_GLOBAL(Type, Name, Addr) Type Name
  #else
      // Injected ASI mode: dereference GTA.exe memory address
      #define NOTSA_GLOBAL(Type, Name, Addr) static inline auto& Name = StaticRef<Type>(Addr)
  #endif
  ```
  State instances are allocated in native process memory, zero-initialized or constructed during subsystem initialization, with no hardcoded pointers.

### 3.3 Graphics & RenderWare Runtime
* **Original**: 1,377 trampolines redirecting to GTA.exe RenderWare routines (`rwplcore`, `rwcore`, `rpworld`, `rpskin`, `rphanim`).
* **Target Architecture**:
  * Drop-in replacement via `librw` (RenderWare 3.x open-source reimplementation).
  * Backends: Modern Direct3D / OpenGL / Vulkan via SDL3 windowing.
  * Custom GTA San Andreas pipelines:
    - `CCustomBuildingDNPipeline` (Day/Night vertex illumination interpolation).
    - `CCustomCarEnvMapPipeline` (Specular reflection and vehicle paint).
    - `CCustomBuildingPipeline` (Atmospheric effects, lights).
    - `CRpSkin` and `CRpHAnim` skeletal animation pipelines.

### 3.4 Platform Abstraction Layer (PAL)
* **Windowing & Events**: Handled via SDL3 (`SDL_CreateWindow`, `SDL_PollEvent`).
* **Input**: Mapped through `CPad` reading SDL3 keyboard, mouse, and game controller events.
* **Audio**: Managed through `CAudioEngine` backed by OpenAL-Soft (`OALBase`, `OALBuffer`, `OALSource`), replacing legacy DirectSound hooks.
* **Virtual Filesystem (VFS)**:
  - Normalizes Windows backslashes (`\`) to POSIX forward slashes (`/`).
  - Provides case-insensitive file lookup for case-sensitive operating systems (Linux/macOS).
  - Mounts `.img` archives (`gta3.img`, `gta_int.img`, `player.img`) via `CdStream`.

### 3.5 World & Spatial Partitioning
* **Grid**: 120 x 120 sectors (`CSector`), spanning 6,000m x 6,000m (50m per sector).
* **Repeat Grid**: 16 x 16 coarse sectors (`CRepeatSector`, 375m per sector) for active dynamic physical entities.
* **Spatial Queries**:
  - `ProcessLineOfSight`: Raycasts against building meshes, ped capsules, and vehicle collision hulls.
  - `FindEntitiesInRange`: Radial bounding queries.
  - `FindGroundZForCoord`: Surface height lookup using collision meshes and static sectors.

### 3.6 Memory Management
* **Pool Architecture**: Entities and resources reside in pre-allocated pools (`CPedPool`, `CVehiclePool`, `CBuildingPool`, `CObjectPool`, `CTaskPool`, `CColModelPool`).
* **CPool Mechanics**: Fast O(1) allocation/deallocation with index + generation bitfields (handling SCM handle resolution).
* **Native Standalone Allocator**: Standard C++ `new`/`delete` and `std::allocator`, eliminating hooks to GTA.exe CRT (`0x82119A`, `0x8214BD`).
