# Technical Blockers: GTA Reversed Standalone Migration

This document catalogs and ranks the technical blockers preventing `gta-reversed` from executing as an independent, native standalone game runtime without `gta_sa.exe`.

---

## 1. Blocker Priority Matrix

| Rank | Blocker Description | Category | Severity | Current Status |
| :---: | :--- | :--- | :---: | :---: |
| **1** | Absence of Native RenderWare Engine (1,377 Thunks to GTA.exe) | Graphics / Core | **CRITICAL** | Planned (Phase 5) |
| **2** | Hardcoded Virtual Memory Globals (2,369 `StaticRef` Instances) | State / Memory | **CRITICAL** | In Design (Phase 1) |
| **3** | Unreversed Function Invocations (838 `plugin::Call` Occurrences) | Logic / Thunks | **CRITICAL** | Planned (Phase 4) |
| **4** | Standalone Executable Target is Dummy Hook Dumper Only | Entry Point | **CRITICAL** | In Progress (Phase 0/1) |
| **5** | Unreversed Core Subsystems (`Interior_c`, `CCam`, `CPedGeometryAnalyser`) | Gameplay / Logic | **HIGH** | Planned (Phase 4/11) |
| **6** | Direct3D9 Device Hooking & Pipeline Coupling (`WindowedMode.cpp`) | Graphics / Platform | **HIGH** | Planned (Phase 5/7) |
| **7** | Global CRT Allocator Hooking (`0x82119A`, `0x8214BD`) | Memory / CRT | **HIGH** | Planned (Phase 1/6) |
| **8** | Platform Layer Coupled to Windows Win32 APIs | Platform | **MEDIUM** | In Progress (Phase 2) |
| **9** | Audio Layer Dependent on DirectSound by Default | Audio | **MEDIUM** | Solved via OpenAL |
| **10**| Filesystem Case Sensitivity & Windows Paths | Assets / VFS | **MEDIUM** | Planned (Phase 3) |
| **11**| ImGui & ToolsMenu Tied to D3D9 Hook Proxy | Debug / Tooling | **LOW** | Planned (Phase 7) |
| **12**| Missing Automated Unit / Regression Test Harness | Testing | **LOW** | Planned (Testing.md) |

---

## 2. Detailed Technical Blocker Analysis

### CRITICAL BLOCKERS (Prevents Execution Entirely)

#### Blocker 1: Absence of Native RenderWare Engine
* **Severity**: **CRITICAL (Showstopper #1)**
* **Impact**: The engine cannot initialize graphics, create camera rasters, load textures, parse `.dff`/`.txd` streams, or render geometry.
* **Affected Files**:
  * `source/game_sa/RenderWare/rw/rwcore.cpp`
  * `source/game_sa/RenderWare/rw/rpworld.cpp`
  * `source/game_sa/RenderWare/rw/rwplcore.cpp`
  * `source/game_sa/RenderWare/rw/rpskin.cpp`
  * `source/game_sa/RenderWare/rw/rphanim.cpp`
  * `source/game_sa/RenderWare/RenderWare.h`
* **Details**: All **1,377 RenderWare functions** in `source/game_sa/RenderWare/rw/*.cpp` are raw trampolines forwarding to GTA SA executable memory (e.g. `RwEngineStart()` calls `0x7F2E70`, `RwCameraBeginUpdate()` calls `0x7EE190`, `RpClumpStreamRead()` calls `0x74B420`). When executed outside `gta_sa.exe`, these jump into unmapped virtual memory and crash immediately.
* **Resolution**: Replace dummy wrapper thunks with `librw` (open-source RenderWare 3.x engine) and port San Andreas custom rendering pipelines.

---

#### Blocker 2: Hardcoded Virtual Memory Globals (`StaticRef`)
* **Severity**: **CRITICAL (Showstopper #2)**
* **Impact**: Accessing any engine singleton, state variable, entity pool, or configuration flag dereferences unmapped memory.
* **Affected Files**:
  * `source/Base.h:163-176`
  * 278+ files across `source/game_sa/**` (**2,369 occurrences**)
* **Details**: Global singletons and states are declared as:
  ```cpp
  static inline auto& ms_pPedPool   = StaticRef<CPedPool*>(0xB74490);
  static inline auto& ms_aSectors   = StaticRef<mdarray<CSector, 120, 120>>(0xB7D0B8);
  static inline auto& ScriptSpace   = StaticRef<array<uint8, SCRIPT_SPACE_SIZE>>(0xA49960);
  static inline auto& RwInitialized = StaticRef<bool>(0xC920E8);
  ```
  In standalone mode, virtual addresses like `0x00B74490` are not mapped in the process space, causing `STATUS_ACCESS_VIOLATION` (`0xC0000005`).
* **Resolution**: Introduce `NOTSA_STANDALONE_NATIVE` mode where `StaticRef` maps to native statically allocated memory or a structured global registry.

---

#### Blocker 3: Unreversed Function Invocations (`plugin::Call`)
* **Severity**: **CRITICAL (Showstopper #3)**
* **Impact**: Game logic crashes whenever an unreversed routine is invoked.
* **Affected Files**:
  * `source/PluginBase.h:33-60`
  * 189 files across `source/game_sa/**` (**838 occurrences**)
  * Primary clusters: `source/game_sa/CarCtrl.cpp` (89 calls), `source/game_sa/Interior/Interior_c.cpp` (52 calls), `source/game_sa/Camera.cpp` (24 calls).
* **Details**: Unreversed methods execute:
  ```cpp
  plugin::Call<0x423F00>();
  ```
  In standalone mode, this executes a CALL instruction into uncommitted virtual memory.
* **Resolution**: Replace calls with verified reverse-engineered code where possible, or structured stubs logging `NOTSA_LOG_WARN("Unimplemented stub: 0x{:X}")` with safe default returns.

---

#### Blocker 4: Standalone Target Exists Only for CI Hook Dumping
* **Severity**: **CRITICAL (Showstopper #4)**
* **Impact**: `gta_reversed.exe` does not contain a boot sequencer for running game simulation.
* **Affected Files**:
  * `source/app/platform/win/WinMain.cpp:534-566`
  * `source/InjectHooksMain.cpp:538-542`
  * `conanfile.py:31`
* **Details**: `WinMain.cpp` contains an explicit error guard:
  ```cpp
  NOTSA_LOG_ERR("This executable is meant to be used for dumping hooks only, see NOTSA_STANDALONE_DUMP_HOOKS_ONLY option");
  return 1;
  ```
  And `conanfile.py` specifies `"standalone": [False, 'dump_hooks_only'] # There's no True yet`.
* **Resolution**: Author a genuine standalone entry point (`source/app/Main.cpp`) that boots the platform layer, initializes `librw`, mounts VFS, and initiates `CGame::Initialise()`.

---

### HIGH BLOCKERS (Subsystems & Runtime Coupling)

#### Blocker 5: Unreversed Core Subsystems
* **Severity**: **HIGH**
* **Impact**: Certain gameplay features (interiors, advanced cameras, ped wall navigation) will fail to operate.
* **Key Missing Classes**:
  * `Interior_c` (`source/game_sa/Interior/Interior_c.cpp`): 52 unreversed functions (0% reversed). Manages shops, fast food, gyms.
  * `CCam` (`source/game_sa/Cam.cpp`): 30 unreversed functions (32% reversed). Manages vehicle follow, cinematic tracking, sniper aim.
  * `CPedGeometryAnalyser` (`source/game_sa/PedGeometryAnalyser.cpp`): 29 unreversed functions (24% reversed). Manages ped climbing, vaulting, obstacle navigation.
  * Vehicle subclasses: `CBike` (18 unreversed), `CTrain` (20 unreversed), `CPlane` (9 unreversed).
* **Resolution**: Implement reverse-engineered routines or port from mature sister projects (`re3` / `reVC` / `plugin-sdk`).

---

#### Blocker 6: Direct3D9 Device & Pipeline Coupling
* **Severity**: **HIGH**
* **Impact**: Rendering system depends on Windows DirectX 9 headers and raw device pointer hooking.
* **Affected Files**:
  * `source/app/platform/win/WindowedMode.cpp` (1,901 lines)
  * `source/game_sa/Pipelines/CustomBuilding/CustomBuildingDNPipeline.cpp`
  * `source/game_sa/Pipelines/CustomCarEnvMap/CustomCarEnvMapPipeline.cpp`
* **Details**: `WindowedMode.cpp` creates a proxy wrapper around `IDirect3DDevice9` retrieved from address `0xC97C28`. Custom pipelines upload raw D3D9 vertex buffers directly.
* **Resolution**: Interface pipelines through `librw`'s backend abstraction (supporting both modern D3D and OpenGL/Vulkan).

---

#### Blocker 7: Global CRT Allocator Hooking
* **Severity**: **HIGH**
* **Impact**: Memory allocations redirect to addresses `0x82119A` and `0x8214BD`.
* **Affected Files**:
  * `source/game_sa/MemoryMgr.cpp:441-457`
  * `source/game_sa/Memory/MemoryHeap.cpp`
* **Details**: Global memory management hooks directly into GTA.exe's embedded MSVC runtime heap.
* **Resolution**: Bypass hooking in standalone mode; route allocations to standard C++ `new`/`delete` and retain `CPool` mechanics.

---

### MEDIUM BLOCKERS (Platform Portability)

#### Blocker 8: Platform Layer Coupled to Windows Win32 APIs
* **Severity**: **MEDIUM**
* **Impact**: Prevents compilation and execution on Linux/macOS.
* **Affected Files**:
  * `source/app/platform/win/WinMain.cpp`
  * `source/app/platform/win/WinPs.cpp`
* **Resolution**: Complete the SDL3 platform backend (`source/app/platform/sdl3/`).

---

#### Blocker 9: Audio Layer Dependent on DirectSound by Default
* **Severity**: **MEDIUM**
* **Impact**: Sound will not work on non-Windows platforms unless OpenAL is enabled.
* **Status**: OpenAL-Soft implementation already exists in `source/game_sa/Audio/OpenAL/` (`OALBase`, `OALBuffer`, `OALSource`).
* **Resolution**: Enable `NOTSA_WITH_OPENAL` by default in standalone builds.

---

#### Blocker 10: Filesystem Case Sensitivity & Windows Paths
* **Severity**: **MEDIUM**
* **Impact**: Asset loading crashes on Linux/macOS due to case differences and backslash separators.
* **Affected Files**: `source/game_sa/FileMgr.cpp`, `source/game_sa/CdStreamInfo.cpp`.
* **Resolution**: Normalize all paths and provide case-insensitive directory caching in `CFileMgr`.

---

### LOW BLOCKERS (Tooling & Quality Assurance)

#### Blocker 11: ImGui & ToolsMenu Tied to D3D9 Hook Proxy
* **Severity**: **LOW**
* **Impact**: In-game debug tools menu cannot render without D3D9 hook proxy.
* **Resolution**: Bind ImGui to SDL3 + `librw` renderer backend.

---

#### Blocker 12: Missing Automated Unit / Regression Test Harness
* **Severity**: **LOW**
* **Impact**: Hard to automatically catch math and simulation regressions without booting the full game.
* **Resolution**: Add GoogleTest / Catch2 test suites for headless subsystems (Math, Collision, Pools, SCM opcodes).
