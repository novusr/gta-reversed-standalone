# Architectural Blockers: GTA Reversed to Standalone Native C++

This document identifies, analyzes, and ranks the technical blockers that currently prevent `gta-reversed` from compiling and executing as an independent native standalone executable without `gta_sa.exe`.

---

## 1. Blocker Priority Hierarchy

```
┌────────────────────────────────────────────────────────────────────────┐
│                        CRITICAL BLOCKERS (Rank 1-4)                    │
│   1. No RenderWare Engine Implementation (1,377 Thunks to GTA.exe)     │
│   2. Hardcoded Virtual Memory Globals (2,369 StaticRef Instances)      │
│   3. Unreversed Function Invocations (838 plugin::Call Occurrences)    │
│   4. Standalone Target Exists Only for CI Hook Metadata Dumping        │
└───────────────────────────────────┬────────────────────────────────────┘
                                    │
┌───────────────────────────────────▼────────────────────────────────────┐
│                          HIGH BLOCKERS (Rank 5-7)                      │
│   5. Unreversed Core Subsystems (Interior_c, CCam, CPedGeometryAnalyser)│
│   6. Direct3D9 Device & Pipeline Coupling                              │
│   7. Global Operator new/delete Hooked to GTA.exe CRT                  │
└───────────────────────────────────┬────────────────────────────────────┘
                                    │
┌───────────────────────────────────▼────────────────────────────────────┐
│                         MEDIUM BLOCKERS (Rank 8-10)                    │
│   8. Platform Layer Coupled to Windows / Win32 Message Loop            │
│   9. Audio Hardware Layer Dependent on DirectSound by Default          │
│  10. Filesystem Case Sensitivity & Windows Path Formats                │
└───────────────────────────────────┬────────────────────────────────────┘
                                    │
┌───────────────────────────────────▼────────────────────────────────────┐
│                          LOW BLOCKERS (Rank 11-12)                     │
│  11. ImGui & ToolsMenu Tied to D3D9 Hook Proxy                         │
│  12. Missing Automated Unit / Regression Test Harness                  │
└────────────────────────────────────────────────────────────────────────┘
```

---

## 2. Detailed Blocker Analysis

### CRITICAL BLOCKERS (Blocks Standalone Execution Entirely)

#### Blocker 1: Total Absence of a RenderWare Engine Implementation
* **Severity**: **CRITICAL (Showstopper #1)**
* **Impact**: The engine cannot initialize graphics, create a camera, load textures, or render a single mesh without `gta_sa.exe`.
* **Affected Files**:
  * `source/game_sa/RenderWare/rw/rwcore.cpp`
  * `source/game_sa/RenderWare/rw/rpworld.cpp`
  * `source/game_sa/RenderWare/rw/rwplcore.cpp`
  * `source/game_sa/RenderWare/rw/rpskin.cpp`
  * `source/game_sa/RenderWare/rw/rphanim.cpp`
  * `source/game_sa/RenderWare/RenderWare.h`
* **Technical Details**:
  All **1,377 RenderWare functions** in `source/game_sa/RenderWare/rw/*.cpp` are raw trampolines forwarding to GTA SA executable memory (e.g. `RwEngineStart()` calls `0x7F2E70`, `RwCameraBeginUpdate()` calls `0x7EE190`, `RpClumpStreamRead()` calls `0x74B420`). When running without `gta_sa.exe`, these addresses point to unmapped virtual memory and trigger immediate execution faults.
* **Resolution**: Replace the RenderWare dummy wrapper files with `librw` (RenderWare 3.x reimplementation) and implement the custom San Andreas pipelines.

---

#### Blocker 2: Hardcoded Virtual Memory Globals (`StaticRef`)
* **Severity**: **CRITICAL (Showstopper #2)**
* **Impact**: Every read and write to game state dereferences invalid memory.
* **Affected Files**:
  * `source/Base.h:163-176`
  * 278+ files across `source/game_sa/**` (**2,369 occurrences**)
* **Technical Details**:
  Game singletons, managers, pools, and configuration flags are defined as:
  ```cpp
  static inline auto& ms_pPedPool   = StaticRef<CPedPool*>(0xB74490);
  static inline auto& ms_aSectors   = StaticRef<mdarray<CSector, 120, 120>>(0xB7D0B8);
  static inline auto& ScriptSpace   = StaticRef<array<uint8, SCRIPT_SPACE_SIZE>>(0xA49960);
  static inline auto& RwInitialized = StaticRef<bool>(0xC920E8);
  ```
  In a standalone process, the virtual address space is randomly assigned by ASLR or standard OS layout. Memory at `0x00B74490` is uncommitted. Any access results in `STATUS_ACCESS_VIOLATION` (`0xC0000005`).
* **Resolution**: Introduce a preprocessor mode (`NOTSA_STANDALONE_NATIVE`) where `StaticRef` redirects to actual static member storage or heap instances allocated by a global engine container.

---

#### Blocker 3: Unreversed Function Invocations (`plugin::Call`)
* **Severity**: **CRITICAL (Showstopper #3)**
* **Impact**: Game logic crashes whenever an unreversed function is invoked.
* **Affected Files**:
  * `source/PluginBase.h:33-60`
  * 189 files across `source/game_sa/**` (**838 occurrences**)
  * Key hotspots: `source/game_sa/CarCtrl.cpp` (89 calls), `source/game_sa/Interior/Interior_c.cpp` (52 calls), `source/game_sa/Camera.cpp` (24 calls).
* **Technical Details**:
  When a method calls an unreversed helper, it executes:
  ```cpp
  plugin::Call<0x423F00>();
  ```
  Without `gta_sa.exe` loaded, this performs a CALL instruction into unallocated address `0x00423F00`.
* **Resolution**:
  1. Complete reverse engineering of the 576 remaining documented functions.
  2. Implement functional stubs or no-ops for non-essential routines (e.g. obscure interior furniture algorithms or analytics).

---

#### Blocker 4: Standalone Target is Currently a Dummy Hook Dumper
* **Severity**: **CRITICAL (Showstopper #4)**
* **Impact**: The existing standalone executable target (`gta_reversed.exe`) cannot run the game loop.
* **Affected Files**:
  * `source/app/platform/win/WinMain.cpp:534-566`
  * `source/InjectHooksMain.cpp:538-542`
  * `conanfile.py:31`
* **Technical Details**:
  `WinMain.cpp` contains an explicit error guard:
  ```cpp
  NOTSA_LOG_ERR("This executable is meant to be used for dumping hooks only, see NOTSA_STANDALONE_DUMP_HOOKS_ONLY option");
  return 1;
  ```
  `InjectHooksMain.cpp` explicitly forbids running game initialization when `NOTSA_STANDALONE` is defined.
* **Resolution**: Author a genuine standalone entry point (`source/app/Main.cpp`) that boots the platform layer, initializes `librw`, mounts the virtual filesystem, loads data files, and runs `CGame::Initialise("DATA\\GTA.DAT")`.

---

### HIGH BLOCKERS (Subsystem Gaps & Runtime Coupling)

#### Blocker 5: Unreversed Core Subsystems
* **Severity**: **HIGH**
* **Impact**: Certain gameplay features (interiors, advanced cameras, pedestrian wall navigation) will fail to operate.
* **Affected Categories**:
  * `Interior_c` (`source/game_sa/Interior/Interior_c.cpp`): 52 unreversed functions (0% reversed). Manages shops, fast food, and gyms.
  * `CCam` (`source/game_sa/Cam.cpp`): 30 unreversed functions (32% reversed). Manages vehicle follow, cinematic tracking, and sniper aim.
  * `CPedGeometryAnalyser` (`source/game_sa/PedGeometryAnalyser.cpp`): 29 unreversed functions (24% reversed). Manages pedestrian climbing, vaulting, and obstacle navigation.
  * Vehicle subclasses: `CBike` (18 unreversed), `CTrain` (20 unreversed), `CPlane` (9 unreversed).
* **Resolution**: Finish reversing these high-priority classes or backport implementations from `re3` / `reVC` / `plugin-sdk`.

---

#### Blocker 6: Direct3D9 Device & Pipeline Coupling
* **Severity**: **HIGH**
* **Impact**: Rendering system depends on Windows DirectX 9 headers and raw device pointer hooking.
* **Affected Files**:
  * `source/app/platform/win/WindowedMode.cpp` (1,901 lines)
  * `source/game_sa/Pipelines/CustomBuilding/CustomBuildingDNPipeline.cpp`
  * `source/game_sa/Pipelines/CustomCarEnvMap/CustomCarEnvMapPipeline.cpp`
* **Technical Details**:
  `WindowedMode.cpp` creates a proxy wrapper around `IDirect3DDevice9` retrieved from address `0xC97C28`. The custom rendering pipelines directly upload raw D3D9 vertex buffers and set D3D9 texture stage states.
* **Resolution**: Abstract rendering pipelines through `librw`'s backend interface (supporting both modern D3D and OpenGL/Vulkan).

---

#### Blocker 7: Global CRT Allocator Hooking
* **Severity**: **HIGH**
* **Impact**: Memory allocation redirects to addresses `0x82119A` and `0x8214BD`.
* **Affected Files**:
  * `source/game_sa/MemoryMgr.cpp:441-457`
  * `source/game_sa/Memory/MemoryHeap.cpp`
* **Technical Details**:
  In DLL mode, `operator new` and `operator delete` bypass standard CRT and call the MSVCRT runtime inside `gta_sa.exe`.
* **Resolution**: Conditionalize global new/delete overloads to standard C++ `<new>` in standalone mode (`#ifndef NOTSA_STANDALONE` already exists in `MemoryMgr.cpp:441`, but needs verification across all custom allocators).

---

### MEDIUM BLOCKERS (Platform & Asset Abstraction)

#### Blocker 8: Platform Layer Tied to Windows APIs
* **Severity**: **MEDIUM**
* **Impact**: Code cannot compile or run natively on Linux/macOS.
* **Affected Files**:
  * `source/app/platform/win/WinMain.cpp`
  * `source/app/platform/win/WinPs.cpp`
  * `source/app/platform/win/WndProc.cpp`
  * `source/app/platform/win/WinInput.cpp`
* **Technical Details**:
  Application startup, message pumping, cursor visibility, sticky-key handling, and display mode selection use Windows Win32 APIs (`SystemParametersInfo`, `DirectInput8Create`, `PeekMessageA`).
* **Resolution**: Migrate platform layer to the existing SDL3 dependency (`conanfile.py:44`, `NOTSA_USE_SDL3`).

---

#### Blocker 9: Audio Layer DirectSound Dependency
* **Severity**: **MEDIUM**
* **Impact**: Fails to produce audio on non-Windows systems without DirectSound.
* **Affected Files**:
  * `source/game_sa/Audio/Hardware/AEAudioHardware.cpp`
  * `source/CMakeLists.txt:292-302`
* **Technical Details**:
  Windows builds default to `USE_DSOUND` and link `dsound.lib`.
* **Resolution**: Standardize on `USE_OPENAL` (`source/game_sa/Audio/OpenAL/`) across all platforms.

---

#### Blocker 10: Filesystem Case Sensitivity & Path Delimiters
* **Severity**: **MEDIUM**
* **Impact**: Asset loading (`models/gta3.img`, `data/gta.dat`) fails on case-sensitive filesystems (Linux, macOS).
* **Affected Files**:
  * `source/game_sa/FileMgr.cpp`
  * `source/game_sa/FileLoader.cpp`
* **Technical Details**:
  Paths are hardcoded with Windows backslashes (e.g. `"MODELS\\COLL\\PEDS.COL"`).
* **Resolution**: Implement a case-insensitive path resolution lookup in `CFileMgr`.

---

### LOW BLOCKERS (Polish & Quality of Life)

#### Blocker 11: ImGui Debug Tools Bound to D3D9 Hook Proxy
* **Severity**: **LOW**
* **Impact**: Developer debug menus (`toolsmenu/`) will not render without D3D9 device interception.
* **Resolution**: Initialize ImGui using SDL3 + librw backend bindings (`imgui_impl_sdl3` and `imgui_impl_opengl3`/`imgui_impl_dx9`).

#### Blocker 12: Lack of Automated Regression Tests
* **Severity**: **LOW**
* **Impact**: Difficult to detect regressions when switching from hooked DLL mode to native standalone execution.
* **Resolution**: Develop automated headless tests checking SCM script execution, math routines, and collision sweeps.
