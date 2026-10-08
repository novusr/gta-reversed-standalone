# Migration Roadmap: GTA Reversed Standalone

This roadmap outlines the phased execution strategy to transition `gta-reversed` from an injected ASI into an independent native C++ runtime.

---

## 1. Migration Lifecycle Status Overview

```text
Phase 0 ──► Phase 1 ──► Phase 2 ──► Phase 3 ──► Phase 4 ──► Phase 5 ──► Phase 6
Baseline    StaticRef   Platform    VFS & File  Stub Unrev  librw       Headless
Validation  Decoupling  (SDL3/OAL)  Case-Sens.  Functions   Integration Boot
[COMPLETED] [IN PROGRESS][PLANNED]  [PLANNED]   [PLANNED]   [PLANNED]   [PLANNED]

Phase 7 ──► Phase 8 ──► Phase 9 ──► Phase 10 ─► Phase 11 ─► Phase 12 ─► Phase 13
Window &    Streaming   Collision   World &     Ped/Vehicle SCM Script  Playable
Renderer    & Assets    & Raycasts  Scene Tick  Gameplay    Missions    Release
[PLANNED]   [PLANNED]   [PLANNED]   [PLANNED]   [PLANNED]   [PLANNED]   [PLANNED]
```

---

## 2. Phase-by-Phase Roadmap

### Phase 0: Baseline Validation & Architectural Setup
* **Status**: **COMPLETED**
* **Goal**: Establish development workflow, architectural source of truth, dependency map, and blocker hierarchy.
* **Key Deliverables**:
  - [x] Complete codebase audit (408k lines, 2,369 `StaticRef`s, 1,377 RW thunks, 838 `plugin::Call`s).
  - [x] Establish autonomous documentation memory in `docs/standalone/`.
  - [x] Document constraints, architectural decision records, and blocker matrix.
  - [x] Verify baseline CMake and Conan configuration for ASI and dump-hooks modes.

---

### Phase 1: `StaticRef` & Storage Decoupling
* **Status**: **IN PROGRESS**
* **Goal**: Eliminate virtual memory address dereferencing for engine state without breaking ASI mode.
* **Key Tasks**:
  - [ ] Define compilation macro `NOTSA_STANDALONE_NATIVE`.
  - [ ] Implement dual-mode storage in `source/Base.h` allowing static variables to resolve to native process memory.
  - [ ] Decouple global allocator hooks in `source/game_sa/MemoryMgr.cpp` for native builds.
  - [ ] Verify clean compilation of core game classes with native memory storage.

---

### Phase 2: Platform Abstraction Layer (SDL3 & OpenAL)
* **Status**: **PLANNED**
* **Goal**: Decouple the application lifecycle and audio from legacy Win32 / DirectSound APIs.
* **Key Tasks**:
  - [ ] Unify window creation and event pumping under SDL3 (`source/app/platform/`).
  - [ ] Route gamepad, keyboard, and mouse inputs from SDL3 events into `CPad`.
  - [ ] Enable OpenAL-Soft audio backend by default for standalone builds.
  - [ ] Remove Win32 message loop dependencies from core game tick.

---

### Phase 3: Filesystem & VFS Normalization
* **Status**: **PLANNED**
* **Goal**: Ensure robust, cross-platform asset loading across Windows, Linux, and macOS.
* **Key Tasks**:
  - [ ] Path normalization in `CFileMgr`: convert all `\` to `/`.
  - [ ] Implement case-insensitive file and directory lookup cache for POSIX filesystems.
  - [ ] Test loading configuration files (`DATA/GTA.DAT`, `DATA/DEFAULT.DAT`).

---

### Phase 4: Stub Unreversed Functions & Eliminate `plugin::Call`
* **Status**: **PLANNED**
* **Goal**: Eliminate fatal segmentation faults caused by calls to unmapped GTA.exe addresses.
* **Key Tasks**:
  - [ ] Audit all 838 `plugin::Call` instances.
  - [ ] Classify each call (Already reversed, simple replacement, stub-able, critical).
  - [ ] Implement structured diagnostic stubs with logging (`NOTSA_LOG_WARN`) and safe default returns.
  - [ ] Provide initial fallback implementations for `Interior_c` and missing camera modes.

---

### Phase 5: `librw` Integration (Core RenderWare Engine)
* **Status**: **PLANNED**
* **Goal**: Integrate a working RenderWare 3.x graphics implementation.
* **Key Tasks**:
  - [ ] Add `librw` as a subproject / dependency in CMake.
  - [ ] Replace 1,377 dummy thunks in `source/game_sa/RenderWare/rw/` with `librw` API calls.
  - [ ] Verify `RwEngineInit`, `RwEngineOpen`, `RwEngineStart`, and `RwCameraCreate`.
  - [ ] Implement GTA San Andreas custom rendering pipelines on top of `librw`.

---

### Phase 6: Headless Engine Bootstrap
* **Status**: **PLANNED**
* **Goal**: Boot the core game simulation loop without requiring an active graphics context.
* **Key Tasks**:
  - [ ] Implement standalone `Main.cpp` entry point.
  - [ ] Run `CGame::InitialiseOnceBeforeRW()`, `CMemoryMgr::Init()`, and `CPools::Initialise()`.
  - [ ] Validate entity pool allocations and memory stability in headless mode.

---

### Phase 7: Window Creation & Basic Renderer Boot
* **Status**: **PLANNED**
* **Goal**: Open an OS window, clear the backbuffer, and display early loading graphics.
* **Key Tasks**:
  - [ ] Bind `librw` D3D9 / OpenGL backend to the SDL3 native window handle.
  - [ ] Execute `DoRWStuffStartOfFrame()`, `RsCameraShowRaster()`, and `DoRWStuffEndOfFrame()`.
  - [ ] Render game splash screens and loading progress bar (`CLoadingScreen::Render()`).

---

### Phase 8: Asset Loading & Streaming Hydration
* **Status**: **PLANNED**
* **Goal**: Mount `.img` archives and load model dictionaries from disk.
* **Key Tasks**:
  - [ ] Initialize `CdStream` with `models/gta3.img` and `models/gta_int.img`.
  - [ ] Parse `gta.dat` through `CFileLoader::LoadLevel()`.
  - [ ] Verify `CStreaming::ConvertBufferToObject` parsing DFF clumps, TXD textures, and COL files.

---

### Phase 9: Collision & Physics Verification
* **Status**: **PLANNED**
* **Goal**: Verify surface height queries, raycasts, and rigid-body mechanics.
* **Key Tasks**:
  - [ ] Load collision archives (`models/coll/peds.col`, `surface.dat`).
  - [ ] Test `CCollision::ProcessColModels` and `CWorld::FindGroundZForCoord`.
  - [ ] Validate Newtonian physics calculations in `CPhysical::ProcessPhysics()`.

---

### Phase 10: World & Scene Spatial Ticking
* **Status**: **PLANNED**
* **Goal**: Populate spatial sectors with static map geometry and render world buildings.
* **Key Tasks**:
  - [ ] Populate `CWorld::ms_aSectors` from `IPL` map placement files.
  - [ ] Run `CRenderer::ConstructRenderList()` for static buildings and roads.
  - [ ] Tick world simulation each frame without memory leaks.

---

### Phase 11: Pedestrian & Vehicle Spawning
* **Status**: **PLANNED**
* **Goal**: Spawn the player ped, load skeletal animations, and drive dynamic vehicles.
* **Key Tasks**:
  - [ ] Spawn `CPlayerPed` at starting coordinates.
  - [ ] Stream `ANIM/PED.IFP` animations and attach bone hierarchies.
  - [ ] Spawn dynamic vehicles (`CAutomobile`) and verify suspension and driving controls via `CPad`.

---

### Phase 12: Mission Scripting (SCM) Engine Activation
* **Status**: **PLANNED**
* **Goal**: Execute San Andreas SCM bytecode and run ambient scripts and missions.
* **Key Tasks**:
  - [ ] Load `data/script/main.scm` into native `ScriptSpace`.
  - [ ] Initialize `CTheScripts::Init()` and tick `CRunningScript::Process()` each frame.
  - [ ] Validate mission scripts, cutscenes, blips, and save/load system.

---

### Phase 13: Standalone Playable Release
* **Status**: **PLANNED**
* **Goal**: Feature-complete, stable, playable standalone GTA San Andreas release.
* **Key Tasks**:
  - [ ] Comprehensive bug fixing and behavioral comparison with ASI mode.
  - [ ] Full audio playback (radio stations, sound effects, ambients).
  - [ ] Packaging and cross-platform installation binaries.
