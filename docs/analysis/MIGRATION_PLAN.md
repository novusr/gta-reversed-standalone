# Standalone Migration Plan & Target Architecture: GTA Reversed

This document evaluates strategic architectural options, defines the target standalone architecture, and details a phased migration plan to evolve `gta-reversed` into an independent native game runtime.

---

## 1. Migration Strategy Evaluation

We evaluate four potential migration paths to achieve a native standalone runtime:

| Evaluation Criterion | Strategy A: Evolutionary In-Place | Strategy B: Fork & Heavy Refactor | Strategy C: Extraction into New Host Engine | Strategy D: Scratch Rewrite / Reference-Only |
| :--- | :--- | :--- | :--- | :--- |
| **Concept** | Gradually eliminate hooks and inject `librw` in-place | Fork repo; rewrite core into modern C++ patterns (smart ptrs, abstractions) | Build clean runtime harness; import GTA gameplay classes into it | Write new modern engine (e.g. ECS); use GTA Reversed only as decomp reference |
| **Development Effort** | **Moderate (6–12 months)** | **High (18–24 months)** | **High (12–18 months)** | **Extreme (3–5+ years)** |
| **Code Reuse** | **90–95%** (retains 400k lines) | **50–60%** (many rewrites) | **70–80%** (gameplay retained) | **<10%** (almost nothing reused) |
| **Behavioral Fidelity** | **Maximum (Near 100%)** | **Moderate (70–80%)** | **High (85–90%)** | **Low (Generic feeling)** |
| **Technical Risk** | **Low to Moderate** | **Very High** | **High** | **Extreme** |
| **Maintainability** | **High** (keeps upstream sync) | **Poor** (diverges completely) | **Moderate** | **High** (clean code, but incomplete) |
| **RenderWare Compat.** | **High** (drop-in via `librw`) | **Low** (requires renderer rewrite) | **High** (via `librw` adapter) | **None** (modern Vulkan/DX12 renderer) |
| **Standalone Feasibility**| **Immediate (Phased)** | **Delayed** | **Delayed** | **Far Future** |
| **Multiplayer Feasibility**| **High** (clean hooks into state)| **High** | **High** | **High** |

---

### Detailed Evaluation of Each Strategy:

#### Strategy A: Evolutionary In-Place Migration (RECOMMENDED)
* **Description**: Retain the existing repository layout, class hierarchies, and 408,000 lines of verified gameplay logic. Introduce a new compilation mode (`NOTSA_STANDALONE_NATIVE`) that:
  1. Compiles all gameplay classes without hooking machinery.
  2. Substitutes `StaticRef<T>(addr)` with native static member storage.
  3. Replaces dummy RenderWare trampolines with `librw`.
  4. Provides a clean SDL3/OpenAL platform runner.
* **Why it wins**: Preserves 100% of the 5+ years of reverse-engineering work and community contributions. Maintains identical timing, physics, AI, and mission logic. Enables dual-mode compilation: contributors can still build the ASI to test against vanilla `gta_sa.exe`, while the standalone target gradually matures.

#### Strategy B: Fork and Heavy Refactor
* **Description**: Aggressively modernize class hierarchies (replace raw pointers with `std::unique_ptr`/`std::shared_ptr`, convert pools into standard containers, rewrite RenderWare into custom render passes).
* **Flaws**: High risk of subtle memory layout bugs, breaks SCM script memory assumptions, diverges irrecoverably from upstream bugfixes, and introduces massive merge conflicts.

#### Strategy C: Extract Gameplay Logic into a New Host Engine
* **Description**: Build a clean external host engine (windowing, audio, rendering via `librw`, streaming) and copy GTA Reversed `.cpp`/`.h` files into it as a gameplay module.
* **Flaws**: SCM scripting, animation blending, entity streaming, and world partitioning are tightly intertwined with the engine core. Separating "engine" from "gameplay" in a 2004 monolithic game engine requires hundreds of artificial adapter interfaces.

#### Strategy D: Start Completely from Scratch
* **Description**: Treat GTA Reversed merely as documentation to write a brand new engine (e.g. in Rust, modern C++23 with Vulkan and EnTT ECS).
* **Flaws**: Re-implementing San Andreas's thousands of edge-case behaviors (291 tasks, 83 events, hundreds of vehicle handling equations, hundreds of SCM opcodes) from scratch is a multi-year project that has historically failed in similar attempts.

---

### **Recommendation: Adopt Strategy A (Evolutionary In-Place Migration)**

---

## 2. Proposed Target Architecture

The target architecture respects GTA San Andreas's proven object-oriented structure while establishing clean platform and rendering boundaries:

```
┌────────────────────────────────────────────────────────────────────────────────┐
│                           PLATFORM ABSTRACTION LAYER                           │
│       SDL3 (Window, Input, Events)    │    OpenAL-Soft (3D Positional Audio)   │
│       std::filesystem / VFS (Archive Mounting & Case-Insensitive Lookup)       │
└───────────────────────────────────────┬────────────────────────────────────────┘
                                        ▼
┌────────────────────────────────────────────────────────────────────────────────┐
│                             ENGINE RUNTIME & CORE                              │
│       librw (RenderWare Graphics 3.x API: Rasters, Clumps, Textures, Shaders)  │
│       Native Memory Manager (Standard C++ <new>, Native CPools)                │
│       Timer & Clock (std::chrono high-resolution ticks)                        │
└───────────────────────────────────────┬────────────────────────────────────────┘
                                        ▼
┌────────────────────────────────────────────────────────────────────────────────┐
│                            ASSET & STREAMING ENGINE                            │
│       CdStream / IMG Archive Reader (gta3.img, gta_int.img)                    │
│       CFileLoader (IDE, IPL, DAT, COL, IFP, TXD, DFF)                          │
│       CStreaming (Memory budget enforcement, LRU cache, Prioritized I/O)       │
└───────────────────────────────────────┬────────────────────────────────────────┘
                                        ▼
┌────────────────────────────────────────────────────────────────────────────────┐
│                           SIMULATION & GAMEPLAY RUNTIME                        │
│                                                                                │
│   ┌─────────────────────┐  ┌─────────────────────┐  ┌──────────────────────┐   │
│   │   WORLD & SCENE     │  │   ENTITY HIERARCHY  │  │   AI & BEHAVIOR      │   │
│   │ CWorld (120x120)    │  │ CPed, CPlayerPed    │  │ CTaskManager (291 T) │   │
│   │ Spatial Hash / Casts│  │ CVehicle, CObject   │  │ CEventHandler (83 E) │   │
│   └──────────┬──────────┘  └──────────┬──────────┘  └──────────┬───────────┘   │
│              │                        │                        │               │
│   ┌──────────┴──────────┐  ┌──────────┴──────────┐  ┌──────────┴───────────┐   │
│   │  COLLISION/PHYSICS  │  │    MISSION & SCM    │  │  SYSTEM MANAGERS     │   │
│   │ CCollision, ColStore│  │ CTheScripts (VM)    │  │ CPopulation, CWanted │   │
│   │ cHandlingDataMgr    │  │ 800+ Script Opcodes │  │ CCarCtrl, CRadar, HUD│   │
│   └─────────────────────┘  └─────────────────────┘  └──────────────────────┘   │
└────────────────────────────────────────────────────────────────────────────────┘
```

> [!NOTE]
> **Why preserve GTA-style classes instead of ECS?**
> GTA's monolithic class hierarchy (`CEntity` -> `CPhysical` -> `CPed` / `CVehicle`) is deeply bound to the mathematical formulas, SCM script commands, and AI task state machines. Refactoring to ECS offers zero behavioral benefit for San Andreas, adds immense cognitive overhead, and risks breaking subtle vehicle handling and pedestrian reaction quirks.

---

## 3. Phased Implementation Roadmap

```
Phase 0 ──► Phase 1 ──► Phase 2 ──► Phase 3 ──► Phase 4 ──► Phase 5 ──► Phase 6
Current     StaticRef   Platform    VFS & File  Stub Unrev  librw       Headless
State       Decoupling  (SDL3/OAL)  Case-Sens.  Functions   Integration Boot

Phase 7 ──► Phase 8 ──► Phase 9 ──► Phase 10 ─► Phase 11 ─► Phase 12 ─► Phase 13
Window &    Streaming   Collision   World &     Ped/Vehicle SCM Script  Playable
Renderer    & Assets    & Raycasts  Scene Tick  Gameplay    Missions    Release
```

---

### Detailed Phase Milestones:

#### Phase 0: Baseline Validation (Current State)
* Ensure existing code builds cleanly in both MSVC and Wine toolchains.
* Snapshot hook database (`docs/hooks.json`).

#### Phase 1: `StaticRef` & Storage Decoupling
* **Objective**: Eliminate raw memory address dereferencing.
* **Mechanism**:
  * Define `NOTSA_STANDALONE_NATIVE`.
  * Update `source/Base.h`: In standalone mode, `StaticRef<T>(addr)` maps to a statically allocated instance or type-specific global registry rather than `reinterpret_cast<T*>(addr)`.
  * Validate compilation without raw address access.

#### Phase 2: Platform Abstraction (SDL3 & OpenAL)
* **Objective**: Decouple from Windows Win32 APIs and DirectSound.
* **Tasks**:
  * Implement clean SDL3 window creation, event dispatch, and input handling in `source/app/platform/`.
  * Activate `USE_OPENAL` by default in CMake for all targets; test `OALBase.cpp`, `OALBuffer.cpp`, `OALSource.cpp`.

#### Phase 3: Filesystem & VFS Normalization
* **Objective**: Cross-platform asset loading.
* **Tasks**:
  * Update `CFileMgr`: Normalize all path separators (`\` -> `/`).
  * Add case-insensitive directory lookup cache for Linux/macOS.

#### Phase 4: Stub Unreversed Functions & Eliminate `plugin::Call`
* **Objective**: Remove hard crashes on unreversed routines.
* **Tasks**:
  * Replace the 838 `plugin::Call` invocations with functional C++ stubs, logging warnings (`NOTSA_LOG_WARN("Unimplemented stub: ...")`) rather than jumping to invalid addresses.
  * Provide fallback implementations for `Interior_c` and missing camera modes.

#### Phase 5: `librw` Integration (Core RenderWare Engine)
* **Objective**: Provide a real RenderWare runtime.
* **Tasks**:
  * Add `librw` as a CMake subproject or Conan dependency.
  * Replace dummy thunks in `source/game_sa/RenderWare/rw/` with direct calls to `librw`.
  * Verify `RwEngineInit`, `RwEngineOpen`, `RwEngineStart`, and `RwCameraCreate`.

#### Phase 6: Headless Engine Bootstrap
* **Objective**: Boot the game loop without rendering.
* **Tasks**:
  * Author `source/app/Main.cpp`.
  * Execute `CGame::InitialiseOnceBeforeRW()`, `CMemoryMgr::Init()`, `CPools::Initialise()`.
  * Verify memory allocation stability without crashing.

#### Phase 7: Window Creation & Basic Renderer Boot
* **Objective**: Display an active window and clear color buffer.
* **Tasks**:
  * Bind `librw` D3D9 / OpenGL backend to the SDL3 window.
  * Run `DoRWStuffStartOfFrame()`, clear camera raster, run `DoRWStuffEndOfFrame()`, and call `RsCameraShowRaster()`.
  * Display game splash screens and loading screen (`CLoadingScreen::Render()`).

#### Phase 8: Asset Loading & Streaming Hydration
* **Objective**: Load game archives from disk.
* **Tasks**:
  * Initialize `CdStream` with `models/gta3.img`.
  * Load `DATA/GTA.DAT` and `DATA/DEFAULT.DAT` through `CFileLoader::LoadLevel()`.
  * Verify `CStreaming::ConvertBufferToObject` parsing DFF clumps, TXD dictionaries, and COL collision files.

#### Phase 9: Collision & Physics Verification
* **Objective**: Ground detection and world collision.
* **Tasks**:
  * Load `models/coll/peds.col` and surface databases (`surface.dat`).
  * Test `CCollision::ProcessColModels` and `CWorld::FindGroundZForCoord`.

#### Phase 10: World & Scene Spatial Ticking
* **Objective**: Spatial partition and static geometry rendering.
* **Tasks**:
  * Populate `CWorld::ms_aSectors` with map buildings (`IPL` placement).
  * Execute `CRenderer::ConstructRenderList()` and render static buildings and roads.

#### Phase 11: Pedestrian & Vehicle Spawning
* **Objective**: Spawn player and test dynamic entity physics.
* **Tasks**:
  * Spawn `CPlayerPed` at Grove Street coordinates.
  * Stream animations (`ANIM/PED.IFP`) and bind bone hierarchy.
  * Spawn ambient vehicles (`CAutomobile`) and verify suspension and driving controls via `CPad`.

#### Phase 12: Mission Scripting (SCM) Engine Activation
* **Objective**: Run game missions and ambient scripts.
* **Tasks**:
  * Load `data/script/main.scm` into native `ScriptSpace`.
  * Run `CTheScripts::Init()` and tick `CRunningScript::Process()` each frame.
  * Verify cutscenes, blips, mission progression, and save/load system.

#### Phase 13: Standalone Playable Release
* **Objective**: Complete end-to-end game playthrough without `gta_sa.exe`.
* **Tasks**:
  * Reversible bugfixes review.
  * Frame limiter and widescreen UI scaling polish.
  * Package standalone binary with license documentation.
