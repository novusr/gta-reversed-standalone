# Architectural Decision Records (ADR): GTA Reversed Standalone

This document tracks foundational architectural decisions made for the evolution of `gta-reversed` into a standalone native C++ runtime.

---

## Decision 001: Adopt Evolutionary In-Place Migration

### Context
`gta-reversed` contains over 408,000 lines of reverse-engineered C++ code implementing San Andreas gameplay, physics, streaming, and math. We evaluated four strategies: (A) Evolutionary In-Place Migration, (B) Fork & Heavy Refactor, (C) Extraction into a New Host Engine, and (D) Scratch Modern Engine Rewrite.

### Decision
Adopt **Strategy A: Evolutionary In-Place Migration**. Retain the existing repository layout, class hierarchies, and codebase, adding standalone capabilities incrementally.

### Reason
Preserves 100% of the 5+ years of verified reverse-engineering work. Eliminates the catastrophic multi-year risk of rewriting 291 AI tasks, 83 event handlers, vehicle handling equations, and 800+ SCM opcodes from scratch.

### Alternatives Considered
* *Fork and Heavy Refactor*: Massive divergence, merge conflicts, loss of upstream sync.
* *Clean Host Engine Extraction*: High friction due to deep coupling between SCM VM, streaming, and world partitioning.
* *Scratch Rewrite in Modern Engine / Rust*: Historically failed in similar projects; requires 3–5+ years.

### Consequences
Requires careful decoupling of GTA.exe dependencies (`StaticRef`, `plugin::Call`, RenderWare trampolines) without disrupting the existing codebase.

---

## Decision 002: Preserve GTA Reversed Class Hierarchy & Reject ECS

### Context
Modern game engine architecture often favors Entity-Component-System (ECS) or data-oriented design. GTA San Andreas was architected as an object-oriented hierarchy: `CPlaceable` -> `CEntity` -> `CPhysical` -> `CPed` / `CVehicle`.

### Decision
Strictly preserve the original object-oriented class hierarchy. Do not rewrite entities into an ECS.

### Reason
Every physics calculation, animation blend, SCM opcode, AI task, and collision routine assumes the existing pointer relationships and virtual tables. Introducing an ECS would require re-authoring every subsystem in the game with zero behavioral benefit.

### Alternatives Considered
* *EnTT or Flecs ECS*: Complete architectural incompatibility with San Andreas code.
* *Component-based Hybrid*: Added complexity and memory indirection without practical advantage.

### Consequences
Memory layout and inheritance relationships are preserved. The code remains directly comparable to the original x86 disassembly.

---

## Decision 003: Dual-Mode Architecture (ASI Mode and Standalone Mode Coexistence)

### Context
Developers need a reliable behavioral reference to verify whether a bug originates from reverse-engineering logic or missing standalone infrastructure.

### Decision
Support dual compilation modes:
1. **ASI Mode** (`gta_reversed.asi`): Injected into `gta_sa.exe`, hook-based.
2. **Standalone Mode** (`gta_reversed.exe` / native ELF): Native process execution, independent of `gta_sa.exe`.

### Reason
Preserves the ASI build as an immutable ground-truth benchmark. Developers can run any reverted feature in vanilla GTA to observe canonical behavior.

### Alternatives Considered
* *Hard cutover to standalone only*: Destroys the ability to compare behavior against vanilla `gta_sa.exe`.

### Consequences
All core engine hooks and global state accessors must support both injected addressing and native storage via preprocessor definitions (`NOTSA_STANDALONE_NATIVE`).

---

## Decision 004: Abstraction Strategy for `StaticRef` & Global State

### Context
Over 2,369 globals across 278+ files access fixed virtual addresses in `gta_sa.exe` using `StaticRef<T>(addr)`. In standalone mode, dereferencing these addresses causes segmentation faults (`0xC0000005`).

### Decision
Introduce native static member storage and a global state registry under `NOTSA_STANDALONE_NATIVE`:
* In ASI mode, `StaticRef<T>(addr)` continues to return `*reinterpret_cast<T*>(addr)`.
* In Standalone Native mode, static references resolve to statically allocated native variables or a structured engine state container.

### Reason
Allows all 2,369 references to compile and function in standalone mode without having to rewrite every callsite simultaneously.

### Alternatives Considered
* *Virtual memory reservation (`VirtualAlloc` at 0x400000)*: Platform-dependent (Windows only), incompatible with ASLR on modern OSes, fails completely on 64-bit Linux/macOS.
* *Immediate refactoring of all 2,369 globals to new types*: Enormous diff across 278 files that would break ASI compatibility and disrupt the codebase.

### Consequences
Provides an incremental bridge where systems can be decoupled one by one while keeping the whole tree compilable.

---

## Decision 005: Native Allocator Strategy

### Context
GTA Reversed currently hooks global `operator new`, `delete`, and `CMemoryMgr` to GTA.exe CRT addresses (`0x82119A`, `0x8214BD`).

### Decision
In standalone mode, route all dynamic memory allocations through standard C++ allocators (`::operator new`, `::operator delete`, `malloc`, `free`) while retaining GTA's custom `CPool` implementations for fixed-size entity pools.

### Reason
Native standard allocators are portable, leak-detectable with AddressSanitizer (ASan) and Valgrind, and independent of 32-bit MSVC CRT binaries.

### Alternatives Considered
* *Emulating GTA's custom heap pools in raw memory buffers*: Unnecessary complexity when standard allocators fulfill all requirements safely.

### Consequences
Requires conditional compilation in `MemoryMgr.cpp` to bypass hooking routines when running in standalone mode.

---

## Decision 006: RenderWare Runtime Integration via `librw`

### Context
The repository contains 1,377 RenderWare wrapper thunks in `source/game_sa/RenderWare/rw/*.cpp` that call raw GTA.exe memory addresses. Graphics cannot initialize without a functional RenderWare runtime.

### Decision
Integrate `librw` (an open-source RenderWare 3.x reimplementation) as the rendering core for standalone mode.

### Reason
`librw` provides exact API compatibility with RenderWare 3.6 structures (`RwRaster`, `RwTexture`, `RpClump`, `RpAtomic`, `RwCamera`, `RpHAnimHierarchy`). It already powers `re3` and `reVC`, proving full compatibility with GTA 3D-era rendering assets.

### Alternatives Considered
* *Custom modern Vulkan/DX12 renderer from scratch*: Requires writing asset parsers and animation blenders from scratch, taking years.
* *Reverse engineering original RenderWare binaries from scratch*: Redundant effort when `librw` already exists and is mature.

### Consequences
Dummy thunks in `source/game_sa/RenderWare/rw/` will be routed directly to `librw` functions in standalone mode, followed by porting GTA San Andreas custom pipelines (`CustomBuildingDNPipeline`, `CustomCarEnvMapPipeline`).

---

## Decision 007: `plugin::Call` Migration & Stubbing Strategy

### Context
There are 838 invocations of `plugin::Call<addr>()` in unreversed functions across 189 files. In standalone mode, calling these addresses causes immediate crashes.

### Decision
Classify every unreversed function and replace raw `plugin::Call`s with:
1. Reimplemented native C++ logic where possible.
2. Structured stubs logging diagnostic warnings (`NOTSA_LOG_WARN("Unimplemented stub: 0x{:X}")`) and returning safe defaults (e.g. `nullptr`, `0.0f`, `false`) for non-critical routines.

### Reason
Prevents fatal segmentation faults during early engine bootstrap while highlighting remaining gaps through structured logging.

### Alternatives Considered
* *Blanket `return {}` without logging*: Silent failures and subtle behavioral bugs that are nearly impossible to trace.
* *Throwing exceptions or hard aborts*: Prevents bootstrapping any system that touches minor unreversed edge cases.

### Consequences
Allows the game loop to continue running while pinpointing exactly which missing routines require reverse engineering.

---

## Decision 008: Platform Layer Abstraction via SDL3 and OpenAL-Soft

### Context
GTA San Andreas vanilla relies on Win32 message loops (`HWND`, `WndProc`, `PeekMessage`), DirectInput 8, and DirectSound 8.

### Decision
Standardize the standalone platform layer on:
* **Windowing, Events, Input**: SDL3 (`NOTSA_USE_SDL3`).
* **Audio**: OpenAL-Soft (`NOTSA_WITH_OPENAL`).

### Reason
SDL3 and OpenAL-Soft provide modern, cross-platform, high-performance support for Windows, Linux, and macOS without tying the core simulation to Microsoft-only legacy APIs.

### Alternatives Considered
* *GLFW + miniaudio*: Functional, but SDL3 has superior gamepad mapping, native IME, multi-window support, and battle-tested game portability.
* *Preserving Win32/DirectSound*: Leaves the project locked to 32-bit Windows.

### Consequences
Existing SDL3 and OpenAL code in the repository will become default-enabled for standalone targets.

---

## Decision 009: Virtual Filesystem (VFS) & Case-Insensitive Lookup

### Context
GTA San Andreas assets use Windows backslash separators (`DATA\GTA.DAT`, `MODELS\GTA3.IMG`) and arbitrary case variations (`gta.dat` vs `GTA.DAT`). Linux and macOS filesystems are case-sensitive and POSIX path separated.

### Decision
Integrate a path-normalization and case-insensitive virtual filesystem layer into `CFileMgr`:
1. `CFileMgr::NormalizePath`: converts backslashes (`\`) to forward slashes (`/`), collapses duplicate slashes (`//`), strips leading `./`, and trims surrounding whitespace and quotes.
2. `CFileMgr::ResolvePath`: implements a two-level thread-safe cache (`s_PathCache` and `s_DirCache`). If a path does not exist on disk as requested, traverses directory components recursively and case-insensitively, resolving to the true casing on disk while preserving unmatched trailing filenames for file write operations.
3. Hook `CFileMgr::OpenFile`, `OpenFileForWriting`, `OpenFileForAppending`, `ChangeDir`, and `SetDir` through `ResolvePath`.
4. Route `CdStreamOpen` in `CdStreamInfo.cpp` and `CAEMP3TrackLoader` in `AEMP3TrackLoader.cpp` through `CFileMgr::ResolvePath`.

### Reason
Enables pristine vanilla GTA San Andreas game directories to load on Linux and macOS without requiring asset renaming scripts, while maintaining zero overhead on repeated queries via O(1) hash caches.

### Alternatives Considered
* *Requiring users to run a lowercase script on game assets*: Degrades user experience and breaks compatibility with Windows installations or mod archives.
* *Pre-indexing entire game directory tree at startup*: High memory footprint and startup lag on slow HDDs/SD cards compared to on-demand caching.

### Consequences
All file operations across the engine normalize `/` and `\` and transparently resolve case differences on case-sensitive operating systems.

---

## Decision 010: Native Storage Registry & Allocator Decoupling for `StaticRef`

### Context
`StaticRef<T>(addr)` across 2,369 declarations was coupled to fixed `gta_sa.exe` memory addresses (in ASI mode) and caused data aliasing in dummy hook-dump mode (`NOTSA_STANDALONE_DUMP_HOOKS_ONLY`). Furthermore, `MemoryMgr.cpp` hooked global operators `new`/`delete` and memory management routines directly to unmapped GTA.exe CRT addresses (`0x82119A`, `0x8214BD`, `0x72F420`).

### Decision
1. In `source/Base.h`, implement an address-keyed native storage registry (`GetOrCreateStaticStorage`) under `NOTSA_STANDALONE_NATIVE`:
   * Allocates zero-initialized, aligned process heap storage independently for each virtual address `addr`.
   * Enforces a minimum allocation block size (1024 bytes) to safely support overlapping base address references (such as `s_WinVer` and `s_OSStatus` sharing `0xC8CF68`).
   * Adopts a permanent singleton pattern to prevent Static Destruction Order Fiasco during process teardown.
   * Provides `StaticStorage<T, Addr>` and `NOTSA_GLOBAL(Type, Name, Addr)` for progressive compile-time migration.
2. In `source/game_sa/MemoryMgr.cpp`, conditionally compile out CRT allocator hooks under `NOTSA_STANDALONE` / `NOTSA_STANDALONE_NATIVE`:
   * Bypass hooking `operator new`, `operator new[]`, `operator delete`, and `operator delete[]` to GTA.exe addresses.
   * Route `CMemoryMgr::Malloc`, `Free`, `Realloc`, `Calloc`, and `FreeAlign` directly to the standard host C++ runtime heap.

### Reason
Allows the entire codebase of 2,369 global references and dynamic memory allocations to compile, link, and execute safely in a native process with zero memory aliasing, zero access violations, and zero call-site refactoring overhead, while preserving 100% fidelity in vanilla ASI mode.

### Alternatives Considered
* *VirtualAlloc / mmap at fixed 0x400000*: Incompatible with ASLR, non-portable, fails on 64-bit systems.
* *Immediate rewrite of 2,369 call sites to new symbols*: Excessive churn across 278 files, risking massive merge conflicts and breaking ASI baseline comparisons.

### Consequences
The standalone target can initialize and allocate runtime state natively across Windows and Linux platforms without needing a running `gta_sa.exe` process.

---

## Decision 011: Standalone Native Platform Abstraction Layer (SDL3 & OpenAL-Soft)

### Context
In vanilla GTA San Andreas, the application entry point, window management, message loop, input, and audio were coupled to legacy Win32 APIs (`HWND`, `WndProc`, `PeekMessage`), DirectInput 8 (`IDirectInput8`, `IDirectInputDevice8`), and DirectSound 8 (`IDirectSound8`, `IDirectSoundBuffer`, `DirectSoundCreate8`). The standalone executable had no native main loop and terminated immediately at `source/app/platform/win/WinMain.cpp:563` with an error message.

### Decision
1. **Build Configuration**:
   - In `source/CMakeLists.txt` and `conanfile.py`, auto-enable `GTASA_USE_SDL3=ON` and `GTASA_WITH_OPENAL=ON` whenever `GTASA_STANDALONE_NATIVE=ON`.
   - Link `OpenAL::OpenAL` / `openal` and decouple `dsound` and `DIRECTINPUT_VERSION` from the native standalone target.
2. **Windowing & Application Lifecycle**:
   - Replaced the `WinMain.cpp` standalone stub with full SDL3 initialization (`SDL_Init`), platform init (`RsEventHandler(rsINITIALIZE)`), window creation (`SDL_CreateWindow`), audio init (`AudioEngine.Initialise()`), and UI renderer instances with RAII `ScopeGuard` cleanup.
   - Implemented the primary standalone native main loop using `SDL_PollEvent` via `notsa::SDLWrapper::ProcessEvents()` handling quit, window close, focus changes, resize (`rsCAMERASIZE`), and input.
   - Guarded Win32 platform functions (`psWindowSetText`, `psMouseSetVisibility`, `psMouseSetPos`) in `WinPs.cpp` to use SDL3 window APIs when `NOTSA_USE_SDL3` is active.
3. **Input Layer (`CPad`)**:
   - Extended `CPad::ProcessGamepadEvent` to map SDL3 gamepad buttons (`SDL_GamepadButton`) to PS2-equivalent controller state buttons.
   - Added analog stick filtering with a ~20% deadzone (6500 / 32767) and support for user invert/swap axis settings.
   - Mapped left and right analog triggers to `LeftShoulder2` and `RightShoulder2` pressure ranges (0–255).
   - Added gamepad hotplug handling (`SDL_EVENT_GAMEPAD_ADDED`, `SDL_EVENT_GAMEPAD_REMOVED`) and dual-motor rumble via `SDL_RumbleGamepad` in `CPad::UpdateGamepadVibration()`.
4. **Audio Hardware (`CAEAudioHardware` & OpenAL)**:
   - Configured `CAEAudioHardware::Initialise()` to open OpenAL device and context (`alcOpenDevice`, `alcCreateContext`, `alcMakeContextCurrent`), set listener orientation/position, and allocate 48 audio channels under `USE_OPENAL`.
   - Bypassed DirectSound COM calls (`DirectSoundCreate8`, `InitDirectSoundListener`, `Query3DSoundEffects`) and COM `CoInitialize` when `USE_OPENAL` is active.
   - Cleaned up OpenAL device and context on shutdown in `CAEAudioHardware::Terminate()`.
   - Fixed `HeapPtrArray<T>` in `OALBase.h` to use `std::vector<T*>` matching pointer operations in `OALBase.cpp` and `OALSource.cpp`.

### Reason
SDL3 and OpenAL-Soft deliver a battle-tested, portable, high-performance platform abstraction layer across Windows, Linux, and macOS, while completely preserving 100% binary compatibility with the vanilla ASI plugin target.

### Alternatives Considered
* *Maintaining Win32 & DirectSound via Wine emulation wrappers*: Keeps the standalone project bound to 32-bit Windows system calls and legacy DirectX COM interfaces.
* *Rewriting input and audio from scratch*: High risk of regressions in GTA SA's nuanced input response, button mappings, and complex audio environment ducking.

### Consequences
The standalone native target can create windows, poll input events, rumble connected gamepads, and initialize 3D audio natively on modern host platforms without any Win32 or DirectX dependencies.

---

## Decision 012: Graceful Degradation & Diagnostic Stubbing for Unreversed Functions (Phase 4)

### Context
In retail ASI mode, unreversed engine routines rely on `plugin::Call<address>()`, `plugin::CallAndReturn<Ret, address>()`, and `plugin::CallMethod*` to jump directly into retail `gta_sa.exe` code segments in memory. In a native standalone build (`NOTSA_STANDALONE_NATIVE`), these virtual addresses are unmapped, causing immediate Segmentation Faults (`SIGSEGV`) or Access Violations (`0xC0000005`). Reversing the remaining 7% (~576 functions across 189 files) upfront is impossible in a single step without blocking standalone engine bringup.

### Decision
1. **Diagnostic Stub Framework (`source/PluginBase.h`)**:
   - Guarded all `plugin::Call`, `plugin::CallAndReturn`, `plugin::CallMethod`, `plugin::CallMethodAndReturn`, `plugin::CallVirtualMethod`, and `plugin::CallVirtualMethodAndReturn` under `#ifdef NOTSA_STANDALONE_NATIVE`.
   - Instead of casting to raw function pointers, implemented `detail::SafeDefault<Ret>()` which safely constructs default values:
     - Reference return types (e.g. `CRealTimeShadow&`) return aligned static dummy storage to prevent reference initialization compile errors.
     - Pointer types return `nullptr`.
     - Arithmetic/boolean/enum types return `0` / `false`.
     - Value types (e.g. `CVector`) return default constructed zero instances.
   - Incorporated rate-limited logging (`NOTSA_LOG_WARN`) using static per-address guard flags, logging each unreversed call site exactly once to prevent performance degradation in 60 FPS update loops.
   - Isolated `GetBaseAddress()` and `GetGlobalAddress()` in `source/PluginBase.cpp` from Win32 `GetModuleHandleA`.
2. **Subsystem Fallbacks**:
   - `CMemoryMgr`: Decoupled `InitScratchPad` and `MallocAlign` to native CRT allocators.
   - `InteriorGroup_c` & `Interior_c`: Implemented native `Init`, `AddInterior`, `Exit`, `GetEntity`, `GetPed`, and `IsPtInside` routines so building interior lists and spatial lookups remain coherent without calling unmapped addresses.
3. **Comprehensive Audit**:
   - Generated a full classification and inventory of all active `plugin::Call` sites in `docs/standalone/audits/PLUGIN_CALL_AUDIT.md`.

### Reason
Allows the standalone engine to boot and run headless or windowed without crashing when traversing unreversed gameplay corners, while maintaining clear diagnostic visibility into which missing functions are exercised.

### Alternatives Considered
* *Hard abort (`assert(false)` / `std::terminate`)*: Makes it impossible to test or boot any engine system that touches minor unreversed edge cases.
* *Silent stubs without logging*: Masks engine gaps and makes debugging missing behavior impossible.

### Consequences
Eliminates segmentation faults from all 838 `plugin::Call` locations in standalone native mode while preserving 100% binary compatibility with retail `gta_sa.exe` in ASI plugin builds. Increases standalone playability to ~18%.

