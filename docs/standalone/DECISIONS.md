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
Integrate a path-normalization and case-insensitive virtual filesystem layer into `CFileMgr`.

### Reason
Enables pristine vanilla GTA San Andreas game directories to load on Linux and macOS without requiring asset renaming scripts.

### Alternatives Considered
* *Requiring users to run a lowercase script on game assets*: Degrades user experience and breaks compatibility with Windows installations or mod archives.

### Consequences
All file openings in `CFileMgr` normalize `/` and `\` and perform case-insensitive directory lookups when files are not found directly.
