# Current State: GTA Reversed Standalone

This document provides the operational truth of the `gta-reversed` repository at this moment.

---

## Current Phase
* **Phase**: **Phase 0 (Completed)** ──► **Phase 1 (In Progress)**
* **Description**: Baseline architectural validation and documentation complete; beginning Phase 1 (`StaticRef` & Storage Decoupling).

---

## Overall Migration Status
* **Status**: **Pre-Alpha / Migration Infrastructure & Storage Decoupling**
* **Standalone Playability**: **0%** (Cannot execute game simulation yet).
* **Codebase Coverage**: 408,000 lines of reverse-engineered C++ logic available in tree; 95% of classes implemented.
* **Compilation Mode**:
  - ASI Mode (`gta_reversed.asi`): Functional and verified against retail `gta_sa.exe`.
  - Standalone Dump-Hooks Mode (`NOTSA_STANDALONE_DUMP_HOOKS_ONLY`): Functional for CI metadata export.
  - Standalone Native Runtime (`NOTSA_STANDALONE_NATIVE`): In architectural design / Phase 1 setup.

---

## Completed
- [x] Full codebase audit and dependency classification (2,369 `StaticRef`s, 1,377 RW thunks, 838 `plugin::Call`s).
- [x] Architectural strategy evaluation (Decided: Evolutionary In-Place Migration, rejecting ECS and scratch engine).
- [x] Establishment of autonomous project memory in `docs/standalone/` (`ARCHITECTURE.md`, `ROADMAP.md`, `DECISIONS.md`, `CONSTRAINTS.md`, `BLOCKERS.md`, `CURRENT_STATE.md`, `TESTING.md`, and phase documents).
- [x] Standalone build flags mapped in `conanfile.py` and `source/CMakeLists.txt` (`GTASA_STANDALONE`, `GTASA_STANDALONE_DUMP_HOOKS_ONLY`).
- [x] Audio backend: OpenAL-Soft abstraction already in tree (`source/game_sa/Audio/OpenAL/`).
- [x] Input backend: SDL3 bindings already present in tree (`source/app/platform/`).

---

## In Progress
- [ ] **Phase 1 Implementation**:
  - Designing non-aliasing native memory storage for `StaticRef` under `NOTSA_STANDALONE_NATIVE` in `source/Base.h`.
  - Adding `GTASA_STANDALONE_NATIVE` compile definition to CMake.
  - Designing allocator detachment in `source/game_sa/MemoryMgr.cpp`.

---

## Not Started
- [ ] Phase 2: Platform Abstraction Layer completion (pure SDL3 message loop & inputs).
- [ ] Phase 3: Filesystem & VFS path normalization / case-insensitivity.
- [ ] Phase 4: Stubbing remaining 838 `plugin::Call` instances with diagnostic warnings.
- [ ] Phase 5: `librw` RenderWare engine integration.
- [ ] Phase 6: Headless engine bootstrap.
- [ ] Phase 7: Window creation and loading screen rendering.
- [ ] Phases 8–13: Streaming, collision, world ticks, ped/vehicle spawning, SCM missions, and final release.

---

## Known Problems
1. **`StaticRef` Memory Faults**: In a standalone process, dereferencing fixed addresses like `0xB74490` causes an immediate `STATUS_ACCESS_VIOLATION` (`0xC0000005`).
2. **Dump-Hooks Storage Aliasing**: In `NOTSA_STANDALONE_DUMP_HOOKS_ONLY`, `StaticRef` returns a single per-type static buffer (`source/Base.h:171`), causing all globals of the same type (e.g. `int32`) to alias the same memory.
3. **No Standalone Game Entry Point**: `source/app/platform/win/WinMain.cpp:557` logs an error and exits with code 1 if run without `dump_hooks_only`.
4. **1,377 Dead RenderWare Thunks**: Every RenderWare API thunk in `source/game_sa/RenderWare/rw/*.cpp` calls raw GTA.exe addresses.
5. **838 Unreversed Calls**: `plugin::Call<addr>()` crashes in standalone mode if invoked.
6. **Allocator Hooking**: `MemoryMgr.cpp` hooks global `operator new`/`delete` to GTA.exe CRT addresses (`0x82119A`, `0x8214BD`).
7. **D3D9 Coupling**: `WindowedMode.cpp` queries `IDirect3DDevice9` from GTA.exe memory address `0xC97C28`.

---

## Remaining GTA.exe Dependencies
* **Virtual Memory Pointers**: 2,369 `StaticRef` instances across 278+ files.
* **Embedded CRT Allocator Addresses**: `0x82119A`, `0x8214BD`.
* **Direct3D Device Hook Address**: `0xC97C28`.
* **Window Callback & Win32 Addresses**: `0xC17040` (`RsGlobal`), `0x748710` (`NOTSA_WinMain`).

---

## Remaining RenderWare Dependencies
* **Total Thunks**: 1,377 functions across `rwplcore.cpp`, `rwcore.cpp`, `rpworld.cpp`, `rpskin.cpp`, `rphanim.cpp`.
* **Subsystems Affected**: Core engine (`RwEngineStart`), rasters/textures (`RwRasterCreate`, `RwTextureRead`), cameras (`RwCameraCreate`), atomics & clumps (`RpClumpStreamRead`), bone animation (`RpHAnimHierarchyCreate`), skinning (`RpSkinAtomicGetHAnimHierarchy`).

---

## Remaining plugin::Call Dependencies
* **Total Invocations**: 838 occurrences across 189 files.
* **Top Hotspots**:
  - `source/game_sa/CarCtrl.cpp`: 89 calls
  - `source/game_sa/Interior/Interior_c.cpp`: 52 calls
  - `source/game_sa/Camera.cpp`: 24 calls
  - `source/game_sa/Entity/Ped/PedGeometryAnalyser.cpp`: 29 calls
  - `source/game_sa/Entity/Vehicle/Bike.cpp`: 18 calls
  - `source/game_sa/Entity/Vehicle/Train.cpp`: 20 calls

---

## Remaining StaticRef Dependencies
* **Total Declarations**: 2,369 declarations across 278 files.
* **Key Subsystems**:
  - `CWorld`: `ms_aSectors` (`0xB7D0B8`), `ms_aRepeatSectors` (`0xB992B8`), `Players` (`0xB7CD98`)
  - `CPools`: `ms_pPedPool` (`0xB74490`), `ms_pVehiclePool` (`0xB74494`), `ms_pBuildingPool` (`0xB74498`)
  - `CStreaming`: `ms_aInfoForModel` (`0x8E4CC0`), `ms_channel` (`0x8E4C40`)
  - `CTheScripts`: `ScriptSpace` (`0xA49960`), `ScriptsArray` (`0xA8B430`)
  - `CTimer`: `m_snTimeInMilliseconds` (`0xB7CB84`), `ms_fTimeStep` (`0xB7CB5C`)

---

## Build Status
* **ASI Target (`gta_reversed.asi`)**: Compiles cleanly with MSVC 19.5+ (C++23) using CMake/Conan.
* **Standalone CI Target (`gta_reversed.exe --dump-hooks-to=...`)**: Compiles and runs in CI for hook dumping.
* **Standalone Native Executable**: Not yet enabled in CMake.

---

## Test Status
* **Hook Registration Validation**: Verified via `docs/hooks.json` generated in CI.
* **Runtime Verification**: ASI target tested against original retail GTA San Andreas v1.0 US.
* **Automated Unit Tests**: None currently configured.

---

## Next Recommended Work
1. **Implement Phase 1 (`StaticRef` & Storage Decoupling)**:
   - Add `NOTSA_STANDALONE_NATIVE` definition to `source/CMakeLists.txt` and `conanfile.py`.
   - Update `source/Base.h` to introduce address-keyed native storage or statically typed native members for standalone mode without memory aliasing.
   - Conditionally bypass CRT allocator hooking in `source/game_sa/MemoryMgr.cpp`.
