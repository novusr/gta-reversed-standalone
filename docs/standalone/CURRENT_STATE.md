# Current State: GTA Reversed Standalone

This document provides the operational truth of the `gta-reversed` repository at this moment.

---

## Current Phase
* **Phase**: **Phase 4 (Completed)** ──► **Phase 5 (Ready to Start)**
* **Description**: Phase 4 (Stub Unreversed Functions & Eliminate plugin::Call) complete: all 838 `plugin::Call` locations decoupled with rate-limited diagnostic logging (`NOTSA_LOG_WARN`) and safe default returns (`detail::SafeDefault<Ret>()`). Core subsystem stubs implemented for `Interior_c`, `InteriorGroup_c`, and `CMemoryMgr`.

---

## Overall Migration Status
* **Status**: **Pre-Alpha / Crash-Free Native Stubs & PAL/VFS Operational**
* **Standalone Playability**: **18%** (Crash-free native stub degradation, asset resolution, windowing, message loop, input, and audio hardware layer operational).
* **Codebase Coverage**: 408,000 lines of reverse-engineered C++ logic available in tree; 95% of classes implemented.
* **Compilation Mode**:
  - ASI Mode (`gta_reversed.asi`): Functional and verified against retail `gta_sa.exe`.
  - Standalone Dump-Hooks Mode (`NOTSA_STANDALONE_DUMP_HOOKS_ONLY`): Functional for CI metadata export.
  - Standalone Native Runtime (`NOTSA_STANDALONE_NATIVE`): Implemented and verified with SDL3, OpenAL, VFS normalization, and safe diagnostic stubs.

---

## Completed
- [x] Full codebase audit and dependency classification (2,369 `StaticRef`s, 1,377 RW thunks, 838 `plugin::Call`s).
- [x] Architectural strategy evaluation (Decided: Evolutionary In-Place Migration, rejecting ECS and scratch engine).
- [x] Establishment of autonomous project memory in `docs/standalone/` (`ARCHITECTURE.md`, `ROADMAP.md`, `DECISIONS.md`, `CONSTRAINTS.md`, `BLOCKERS.md`, `CURRENT_STATE.md`, `TESTING.md`, and phase documents).
- [x] Standalone build flags mapped in `conanfile.py` and `source/CMakeLists.txt` (`GTASA_STANDALONE`, `GTASA_STANDALONE_DUMP_HOOKS_ONLY`, `GTASA_STANDALONE_NATIVE`).
- [x] **Phase 1 (`StaticRef` & Storage Decoupling)**:
  - Non-aliasing native memory storage for `StaticRef` under `NOTSA_STANDALONE_NATIVE` in `source/Base.h`.
  - Added `GTASA_STANDALONE_NATIVE` option to CMake, Conan, and CI action.
  - Allocator CRT hooks detached in `source/game_sa/MemoryMgr.cpp` (bypassing `0x82119A` and `0x8214BD`).
  - Added `NOTSA_GLOBAL` macro and `notsa::NativeStaticRef` compile-time template storage.
- [x] **Phase 2 (Platform Abstraction Layer: SDL3 & OpenAL)**:
  - Auto-enabled `GTASA_USE_SDL3=ON` and `GTASA_WITH_OPENAL=ON` when `GTASA_STANDALONE_NATIVE=ON` in CMake and Conan.
  - Bootstrapped native standalone entry point and frame pump in `source/app/platform/win/WinMain.cpp` using `SDL_Init`, `SDL_CreateWindow`, `SDL_PollEvent`, and RAII ScopeGuards.
  - Connected SDL3 events to `CPad`: gamepad buttons, analog axis deadzones (~20%), inverted/swapped axis prefs, analog triggers (0-255), hotplugging, and rumble via `SDL_RumbleGamepad`.
  - Standardized audio backend to OpenAL-Soft: `CAEAudioHardware::Initialise()` opens OpenAL device/context and configures 48 channels, while bypassing DirectSound COM interfaces (`DirectSoundCreate8`, `InitDirectSoundListener`, `Query3DSoundEffects`).
  - Fixed `HeapPtrArray` raw-pointer vector in `OALBase.h` for seamless buffer and source tracking.
  - Maintained 100% Dual-Mode compatibility with the vanilla ASI plugin target.
- [x] **Phase 3 (Filesystem & VFS Normalization)**:
  - Implemented `CFileMgr::NormalizePath` (converting `\` to `/`, collapsing duplicate slashes, stripping `./`, trimming whitespace/quotes).
  - Implemented thread-safe, cached case-insensitive path resolver `CFileMgr::ResolvePath` and `ClearPathCache`.
  - Integrated `CFileMgr::OpenFile`, `OpenFileForWriting`, `OpenFileForAppending`, `ChangeDir`, `SetDir`, and `SetDirMyDocuments` with VFS resolution and POSIX directory functions.
  - Routed archive reader `CdStreamOpen` in `CdStreamInfo.cpp` through `CFileMgr::ResolvePath`.
  - Converted `CAEMP3TrackLoader` audio table loaders to use `CFileMgr` for VFS compliance.
  - Unit-tested and validated against mixed-case retail directory structures.
- [x] **Phase 4 (Stub Unreversed Functions & Eliminate plugin::Call)**:
  - Created non-crashing diagnostic stub framework in `source/PluginBase.h` supporting reference types, pointers, structs, and primitives.
  - Added rate-limited `NOTSA_LOG_WARN` logging once per address site.
  - Decoupled `CMemoryMgr::InitScratchPad` and `MallocAlign` to native CRT allocators.
  - Implemented minimal native fallbacks for `InteriorGroup_c` and `Interior_c` to support traversal without crashes.
  - Audited and published full taxonomy of 838 calls in `docs/standalone/audits/PLUGIN_CALL_AUDIT.md`.

---

## In Progress
- [ ] **Phase 5: `librw` RenderWare Engine Integration**:
  - Decoupling 1,377 RenderWare API thunks in `source/game_sa/RenderWare/rw/*.cpp` from retail GTA.exe pointers to modern `librw` implementation.

---

## Not Started
- [ ] Phase 6: Headless engine bootstrap.
- [ ] Phase 7: Window creation and loading screen rendering.
- [ ] Phases 8–13: Streaming, collision, world ticks, ped/vehicle spawning, SCM missions, and final release.

---

## Known Problems
1. **`StaticRef` Memory Faults**: Resolved for standalone native mode via thread-safe, non-aliasing native storage registry in `source/Base.h`.
2. **Dump-Hooks Storage Aliasing**: Addressed in `NOTSA_STANDALONE_NATIVE`; legacy single-buffer behavior retained only in `NOTSA_STANDALONE_DUMP_HOOKS_ONLY` for CI compatibility.
3. **No Standalone Game Entry Point**: Resolved in Phase 2 via SDL3 bootstrap and event pump in `WinMain.cpp`.
4. **1,377 Dead RenderWare Thunks**: Every RenderWare API thunk in `source/game_sa/RenderWare/rw/*.cpp` calls raw GTA.exe addresses (Target of Phase 5).
5. **838 Unreversed Calls**: Resolved in Phase 4 via non-crashing diagnostic stubs (`SafeDefault<Ret>`) and subsystem fallbacks.
6. **Allocator Hooking**: Resolved for standalone mode; bypasses `0x82119A` and `0x8214BD` CRT hooks and routes to standard compiler/OS runtime heap.
7. **D3D9 Coupling**: `WindowedMode.cpp` queries `IDirect3DDevice9` from GTA.exe memory address `0xC97C28`.

---

## Remaining GTA.exe Dependencies
* **Virtual Memory Pointers**: 2,369 `StaticRef` instances across 278+ files (Decoupled at runtime via native storage registry in Phase 1).
* **Embedded CRT Allocator Addresses**: Detached in standalone modes (`MemoryMgr.cpp`).
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
* **Standalone Native Target (`GTASA_STANDALONE_NATIVE=ON`)**: Configured in CMake and Conan; builds native executable.

---

## Test Status
* **Hook Registration Validation**: Verified via `docs/hooks.json` generated in CI.
* **Runtime Verification**: ASI target tested against original retail GTA San Andreas v1.0 US.
* **Native Storage Decoupling Verification**: Validated with non-aliasing unit tests under GCC and Clang for primitive, array, pointer, and scoped references.

---

## Next Recommended Work
1. **Implement Phase 2 (Platform Abstraction Layer - SDL3 Integration)**:
   - Modernize standalone entry point in `WinMain.cpp`.
   - Wire SDL3 message polling and window management.
   - Decouple DirectInput8 / Win32 mouse & keyboard in `CPad`.
