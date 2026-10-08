# Codebase Analysis: GTA San Andreas Reversed (gtasa-reversed)

## 1. Project Overview & Scope

`gtasa-reversed` is an open-source reverse-engineering project dedicated to decompiling and completely reimplementing **Grand Theft Auto: San Andreas** into modern C++ (C++23 standard), documenting every internal class, data structure, and function.

* **Repository Workspace**: `/home/novusr/Desktop/gta-reversed`
* **Target Game Build**: Grand Theft Auto: San Andreas **"Compact exe"** (unpacked 1.0 US executable, exactly **`5,189,632 bytes` / 4.94 MiB**).
* **Current Language Standard**: C++23 (`set(CMAKE_CXX_STANDARD 23)` in `CMakeLists.txt:13`).
* **Source Tree Volume**: **408,147 lines of code** across **2,264 files** (`.cpp`, `.h`, `.hpp`).
* **Primary Execution Form**: Dynamic link library (`.asi` module / Windows PE DLL) injected into the address space of `gta_sa.exe` via an ASI loader (e.g. Silent's ASI Loader).

---

## 2. Reimplementation Completeness & Verification

According to automated CI tracking generated from the project's hook database (`docs/hooks.json` and `docs/ReversedClasses.md`, updated at commit `43f55d06` on Oct 04, 2026):

```
Total Documented Functions:  8,025
Reimplemented Functions:     7,449 (92.82%)
Unreversed Functions:          576 (7.18%)
Total Categories / Classes:    702
Completely Reversed:           587 categories (83.6%)
Partially Reversed:            112 categories (16.0%)
Not-at-all Reversed:             3 categories (0.4%)
```

### Breakdown of Function Reimplementation State
* **Reversed Functions (7,449)**: Completely rewritten in modern C++ within `source/game_sa/**` and registered via `RH_ScopedInstall`, `RH_ScopedGlobalInstall`, or `RH_ScopedVirtualInstall`.
* **Partially Reversed Classes (112 categories)**: Classes where core public methods are reversed, but complex subroutines or internal algorithms still delegate to the original executable via `plugin::Call<address>(...)` or have `.reversed = false` set in hook options.
* **Not-at-all Reversed Classes (3 categories)**:
  1. `CTaskComplexGangFollower` (7 functions) — gang member following behaviors.
  2. `FurnitureSubGroup_c` (3 functions) — interior furniture layout grouping.
  3. `Interior_c` (52 functions) — procedural/streamed interior placement and shopping spaces.

---

## 3. Build System & Target Configuration

### 3.1 Build Tools & Prerequisites
* **Compiler**: Microsoft Visual Studio MSVC 2026 / v143+ (Windows x86 32-bit target).
* **Package Manager**: Conan 2.x (`conanfile.py`).
* **Build Generator**: CMake >= 4.2.0 (`CMakeLists.txt:1`).
* **Cross-Compilation**: Experimental Linux-to-Windows build via Wine and MSVC wrappers (`contrib/msvc-wine/`).

### 3.2 Key CMake Options (`source/CMakeLists.txt:8-33`)
| Option | Default | Purpose in Codebase |
| :--- | :--- | :--- |
| `GTASA_STANDALONE` | `OFF` | Switches target from `add_library(MODULE)` (`.asi`) to `add_executable(WIN32)` (`.exe`). |
| `GTASA_STANDALONE_DUMP_HOOKS_ONLY` | `OFF` | Enables headless CLI mode to export registered hooks to JSON without running game systems. |
| `GTASA_USE_SDL3` | `OFF` | Compiles SDL3 input and window initialization (`NOTSA_USE_SDL3`). |
| `GTASA_WITH_OPENAL` | `OFF` (Win32) / `ON` (others) | Compiles OpenAL hardware audio backend instead of DirectSound (`USE_OPENAL`). |
| `GTASA_UNITY_BUILD` | `OFF` | Enables jumbo/batch compilation (batch size 16) for accelerated build times. |
| `GTASA_WITH_SCRIPT_COMMAND_HOOKS` | `OFF` | Registers script command hooks into the UI. |

### 3.3 Third-Party Dependencies (`conanfile.py:41-57`)
* `sdl/3.4.14`: Platform windowing, input events, controller management.
* `nlohmann_json/3.12.0`: Hook metadata export and configuration parsing.
* `spdlog/1.17.0`: Engine logging (`notsa::Logging`).
* `tracy/cci.20220130`: High-resolution telemetry and profiling (`ZoneScoped`).
* `imgui/1.92.9b-docking`: In-game developer debugging menu (`source/toolsmenu/`).
* `boost/1.91.0` (Header-only): Utility algorithms and container extensions.
* `ogg/1.3.5` & `vorbis/1.3.7`: Radio and compressed audio stream decoding.
* `libjpeg-turbo/3.2.0`: In-game photo album and splash texture loading.

---

## 4. Current Architecture Paradigm: Inside-Out Injection

The project currently operates under an **Inside-Out Replacement Paradigm**:
```
┌──────────────────────────────────────────────────────────┐
│                   Original gta_sa.exe                    │
│                                                          │
│  ┌───────────────────────┐    ┌───────────────────────┐  │
│  │ RenderWare 3.6 Engine │    │  Static Data Segments │  │
│  │ (D3D9 / Rasters / VBs)│    │  (0x850000 - 0xC9FFFF)│  │
│  └───────────▲───────────┘    └───────────▲───────────┘  │
│              │                            │              │
│              │ Function Thunks            │ StaticRef<T> │
│              │ (0x7F2E70, etc.)           │ (0xB7290C)   │
│              │                            │              │
│  ┌───────────┴────────────────────────────┴───────────┐  │
│  │                 gta_reversed.asi                   │  │
│  │                                                    │  │
│  │  - 7,449 Reversed Modern C++ Functions             │  │
│  │  - ReversibleHooks Manager (7,002 active hooks)    │  │
│  │  - ImGui Debug Menus & Tooling                     │  │
│  └────────────────────────────────────────────────────┘  │
└──────────────────────────────────────────────────────────┘
```

1. The game process starts through `gta_sa.exe`.
2. The ASI loader loads `gta_reversed.asi` into the process address space during `DLL_PROCESS_ATTACH` (`source/dllmain.cpp:27`).
3. `InjectHooksMain()` (`source/InjectHooksMain.cpp:535`) installs detour hooks (trampolines or VMT swaps) on 7,002 functions.
4. When `gta_sa.exe` calls a hooked function, control jumps into `gta_reversed.asi`.
5. If the reversed function needs data, it reads from/writes to the original executable's static memory using `StaticRef<T>(address)` (`source/Base.h:164`).
6. If the reversed function needs unreversed logic, it calls back into `gta_sa.exe` via `plugin::Call<address>(...)` (`source/PluginBase.h:33`).
7. If the reversed function interacts with RenderWare (rendering, atomics, textures), it invokes wrapper functions in `source/game_sa/RenderWare/rw/` that invoke original RenderWare routines statically compiled into `gta_sa.exe`.

---

## 5. Architectural Assumptions & Technical Debt Inherited from GTA.exe

1. **32-Bit Pointer Size (x86 ILP32)**:
   All memory structures, offsets, vtable indices, and packed bitfields are rigidly tailored to 32-bit layout. Pointers are assumed to be 4 bytes (`uintptr` is `uint32_t`). Compiling for 64-bit (`x86_64` or `arm64`) would immediately break packed binary structures, game save loading, SCM pointers, and binary resource deserialization.
2. **Absolute Virtual Memory Layout**:
   Over **2,369 instances** of `StaticRef<T>(address)` bind code to absolute Windows 32-bit virtual addresses (`0x00400000` to `0x00C9FFFF`). In a native standalone executable without `gta_sa.exe`, these addresses are invalid and cause instant access violations.
3. **Hardcoded Calling Conventions**:
   Functions use `__cdecl`, `__thiscall`, and `__stdcall` with specific register allocations (`EAX`, `ECX`, `EDX`) matching MSVC 6.0 / Visual C++ 2003 compilation of the original game executable.
4. **Statically Bound RenderWare 3.6**:
   GTA SA was built with Criterion Software's RenderWare 3.6 SDK statically linked into the executable. GTA Reversed has no internal RenderWare engine; its RenderWare `.cpp` files are just thin wrappers invoking addresses in `gta_sa.exe`.
5. **MSVCRT Allocator Coupling**:
   Global `operator new` and `operator delete` in `source/game_sa/MemoryMgr.cpp:441-457` forward directly to addresses `0x82119A` and `0x8214BD` inside the original executable.
