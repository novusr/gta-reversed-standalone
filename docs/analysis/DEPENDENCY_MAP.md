# Dependency Map & Classification: GTA Reversed

This document classifies every major system and component in `gta-reversed` into four architectural dependency tiers:
* **Tier A — Already Standalone-Friendly**: Can run in a standalone engine with minimal or no modification.
* **Tier B — Needs Adaptation**: Clean, high-fidelity logic, but coupled to GTA runtime infrastructure (globals, RenderWare types, or calling conventions).
* **Tier C — Strongly Coupled to `gta_sa.exe`**: Directly relies on original executable addresses, hooks, memory layouts, or binary thunks.
* **Tier D — Must Be Replaced**: Must be completely discarded and rewritten for native standalone execution.

---

## 1. Summary Matrix

| Tier | Component Count | Characteristics | Examples |
| :--- | :--- | :--- | :--- |
| **A: Standalone-Friendly** | ~150 classes / files | Pure math, generic containers, self-contained algorithms | `CVector`, `CMatrix`, `CPool<T>`, `CCollision` primitives |
| **B: Needs Adaptation** | ~1,800 classes / files | High-fidelity gameplay code coupled to `StaticRef` or RenderWare pointers | `CWorld`, `CPed`, `CVehicle`, `CTaskManager`, `CStreaming`, `CTheScripts` |
| **C: Strongly Coupled** | ~200 classes / modules | Direct binary addresses, trampolines, unreversed function thunks | `StaticRef` instances, `plugin::Call`, `RenderWare/rw/*.cpp`, VMT hooks |
| **D: Must Be Replaced** | ~20 modules | ASI injection scaffolding, detour engine, Win32-only legacy glue | `dllmain.cpp`, `ReversibleHooks`, `WindowedMode` device proxy |

---

## 2. Detailed Classification & Rationale

### Tier A: Already Standalone-Friendly

These modules do not dereference `gta_sa.exe` pointers and contain clean modern C++ implementations:

1. **Math & Linear Algebra (`source/game_sa/Core/`)**:
   * `CVector`, `CVector2D`, `CMatrix`, `CRect`, `CQuaternion`, `CMaths`.
   * *Status*: 100% self-contained. Fast, vector-friendly math operations without external dependencies.
2. **Generic Container Templates (`source/game_sa/Core/`, `source/game_sa/Pools/`)**:
   * `CPool<T, S>` (`source/game_sa/Core/Pool.h`): Implements slotted allocation, generational handles, and buffer memory management entirely in C++.
   * `CLinkList<T>`, `CPtrList<T>`, `CPtrNode<T>`, `CQueue<T>`, `notsa::mdarray`.
   * *Status*: Fully standalone.
3. **Collision Primitives & Math Algorithms (`source/game_sa/Collision/`)**:
   * `CColSphere`, `CColBox`, `CColLine`, `CColTriangle`, `CColTrianglePlane`, `CBoundingBox`.
   * Intersection tests (`TestSphereSphere`, `TestLineTriangle`, `TestSphereBox`, `CalculateColPointInsideBox`).
   * *Status*: Mathematical geometry code with zero executable dependencies.
4. **Reversible Bugfix Framework (`source/reversiblebugfixes/`)**:
   * `ReversibleBugFix`, `Bugs.hpp`.
   * *Status*: Clean toggleable bugfix descriptors usable in any runtime.
5. **Configuration & Utility Helpers (`source/extensions/`)**:
   * `Configuration.hpp`, `CommandLine.cpp`, `ci_string.hpp`, `KeyGen.cpp`, `utility.hpp`.
   * *Status*: Modern standard library utilities with no game executable ties.

---

## 3. Tier B: Needs Adaptation (Logic Reusable, Infrastructure Coupled)

These systems represent the core value of GTA Reversed (~400,000 lines of verified gameplay logic). Their algorithmic content is completely written in C++, but they currently depend on:
1. Hardcoded global addresses (`StaticRef`).
2. RenderWare runtime pointers (`RwObject*`, `RpClump*`, `RwFrame*`).
3. Calling unreversed helper functions.

### B.1 `CGame` (`source/game_sa/Game.cpp`)
* **Why it needs adaptation**:
  * Lifecycle functions (`Init1`, `Init2`, `Init3`, `Process`, `Shutdown`) are fully written in C++.
  * *Coupling*: Calls `InitialiseRenderWare()` which invokes dummy RenderWare wrappers (`0x7F2E70`), and reads global level/area flags via `StaticRef`.
  * *Required Adaptation*: Replace `StaticRef` globals with regular static members; replace `InitialiseRenderWare` with `librw` initialization.

### B.2 `CWorld` (`source/game_sa/World.cpp`)
* **Why it needs adaptation**:
  * Sector hashing (120x120 sectors), entity lists, raycasts, ground queries, and spatial traversal are 100% reversed.
  * *Coupling*: `ms_aSectors` (`0xB7D0B8`), `ms_aRepeatSectors` (`0xB992B8`), and `Players` (`0xB7CD98`) are `StaticRef` instances. Queries pass `RpWorld*`.
  * *Required Adaptation*: Allocate sector buffers inside a game instance class; bind spatial queries to the native scene representation.

### B.3 `CEntity`, `CPhysical`, `CPed`, `CVehicle`, `CObject` (`source/game_sa/Entity/**`)
* **Why it needs adaptation**:
  * Behavior, physics equations, states, damage calculations, and handling math are 94–99% reversed.
  * *Coupling*: Each entity stores `RwObject* m_pRwObject;`. Constructors call `CModelInfo` which delegates clump instantiation to RenderWare. Destruction calls `CameraDestroy` and `RwFrameDestroy`.
  * *Required Adaptation*: Retain full class layouts and behavior logic, but wire `m_pRwObject` to `librw` clumps and atomics.

### B.4 Task & AI Subsystems (`source/game_sa/Tasks/**`)
* **Why it needs adaptation**:
  * Over 291 task types are completely implemented in C++.
  * *Coupling*: Tasks allocate using pool managers (`CTaskPool`), access peds, and evaluate skeletal animation nodes through `RpHAnimHierarchy`.
  * *Required Adaptation*: Rebind `CTaskPool` to native heap/pool memory; connect bone lookup to native animation hierarchy.

### B.5 Event Subsystems (`source/game_sa/Events/**`)
* **Why it needs adaptation**:
  * 83 event classes and response calculators are fully written.
  * *Coupling*: Uses `CEventPool` at `0xB744AC` and refers to `CWorld::Players` via `StaticRef`.
  * *Required Adaptation*: Decouple pool instantiation from hardcoded memory addresses.

### B.6 `CStreaming` & `CdStream` (`source/game_sa/Streaming.cpp`, `CdStreamInfo.cpp`)
* **Why it needs adaptation**:
  * 94 out of 94 functions (100%) are completely reversed. Streaming cache, model priority queues, and memory budget managers are pure C++.
  * *Coupling*: `ConvertBufferToObject()` calls `_rwStreamInitialize`, `RpClumpStreamRead`, and `RtDictSchemaStreamReadDict`. Channel buffers use fixed memory offsets.
  * *Required Adaptation*: Rebind stream initialization to `librw`'s `RwStream` and standard file streams.

### B.7 `CTheScripts` (SCM Virtual Machine) (`source/game_sa/Scripts/**`)
* **Why it needs adaptation**:
  * Bytecode execution loop and hundreds of opcodes are fully reversed in modern C++.
  * *Coupling*: `ScriptSpace` is hardcoded at `0xA49960` via `StaticRef`. Globals and thread stacks reference static executable buffers.
  * *Required Adaptation*: Allocate `ScriptSpace` as a dynamic `std::vector<uint8>` loaded directly from `data/script/main.scm`.

### B.8 `CAnimManager` & `RpAnimBlend` (`source/game_sa/Animation/**`)
* **Why it needs adaptation**:
  * IFP parser, animation dictionary loading, and blending algorithms are 98% reversed.
  * *Coupling*: Directly alters `RpHAnimHierarchy` matrices and clumps via function pointers.
  * *Required Adaptation*: Connect to `librw`'s `rphanim` plugin.

### B.9 Audio System (`source/game_sa/Audio/**`)
* **Why it needs adaptation**:
  * Mixing logic, vehicle acoustic profiles, and radio managers are fully reversed.
  * *Coupling*: Default configuration defaults to DirectSound (`USE_DSOUND`) and `0x...` hardware callbacks.
  * *Required Adaptation*: Standardize unconditionally on the existing `USE_OPENAL` OpenAL-Soft backend (`source/game_sa/Audio/OpenAL/`).

### B.10 Input System (`source/game_sa/Pad.cpp`, `source/app/platform/win/WinInput.cpp`)
* **Why it needs adaptation**:
  * Pad processing, key bindings, and mouse look are reversed.
  * *Coupling*: Windows DirectInput8 device initialization and Win32 message hook dependencies.
  * *Required Adaptation*: Complete and standardize on the experimental `source/game_sa/Pad_SDL.cpp` SDL3 implementation.

### B.11 Filesystem (`source/game_sa/FileMgr.cpp`)
* **Why it needs adaptation**:
  * Wrapper around stdio `FILE*`.
  * *Coupling*: Hardcodes Windows backslashes (`\`) and case-sensitive file assumptions that fail on Linux/macOS.
  * *Required Adaptation*: Add path normalization (`std::filesystem::path` or case-insensitive VFS fallback).

---

## 4. Tier C: Strongly Coupled to `gta_sa.exe`

These components cannot function without `gta_sa.exe` present in memory.

### C.1 `StaticRef<T>(address)` (`source/Base.h:163-176`)
* **Count**: **2,369 occurrences** across the entire codebase.
* **Mechanism**:
  ```cpp
  template<typename T>
  T& StaticRef(uintptr addr) {
  #ifdef NOTSA_STANDALONE_DUMP_HOOKS_ONLY
      alignas(alignof(T)) static uint8 buf[sizeof(T)]{};
      return *reinterpret_cast<T*>(buf);
  #else
      return *reinterpret_cast<T*>(addr);
  #endif
  }
  ```
* **Why it is coupled**: Directly reads and writes memory addresses in the process address space from `0x00400000` to `0x00C9FFFF`. In a standalone executable, those addresses are not mapped, causing immediate segmentation faults / access violations (`0xC0000005`).

### C.2 `plugin::Call<address>(...)` (`source/PluginBase.h:33-60`)
* **Count**: **838 occurrences** across 189 files.
* **Mechanism**:
  ```cpp
  template <unsigned int address, typename... Args>
  void Call(Args... args) {
      reinterpret_cast<void(__cdecl*)(Args...)>(address)(args...);
  }
  ```
* **Why it is coupled**: Executes machine code at raw absolute addresses inside `gta_sa.exe`. In a standalone binary, there is no code at those addresses.

### C.3 RenderWare Wrapper Thunks (`source/game_sa/RenderWare/rw/*.cpp`)
* **Count**: **1,377 hardcoded addresses**.
* **Mechanism**:
  ```cpp
  RwBool RwEngineStart() {
      return ((RwBool(__cdecl *)(void))0x7F2E70)();
  }
  ```
* **Why it is coupled**: RenderWare is not implemented in GTA Reversed. These files merely export C-style functions that call the binary routines inside `gta_sa.exe`.

### C.4 Global CRT Allocator Hook (`source/game_sa/MemoryMgr.cpp:441-457`)
* **Mechanism**:
  ```cpp
  void* operator new(size_t size) {
      return plugin::CallAndReturn<void*, 0x82119A, size_t>(size);
  }
  void operator delete(void* p) {
      plugin::Call<0x8214BD, void*>(p);
  }
  ```
* **Why it is coupled**: Hooks the global C++ memory allocator into MSVCRT `malloc` and `free` within `gta_sa.exe`.

### C.5 Direct3D9 Device Hooks (`source/app/platform/win/WindowedMode.cpp`)
* **Mechanism**: Reads `GetD3D9Device()` from `0xC97C28` and hooks D3D9 vtable entry points to intercept `EndScene` and `Present` for ImGui rendering.

---

## 5. Tier D: Must Be Replaced

These systems are architectural artifacts of running as an injected DLL/ASI plugin and must be eliminated in a standalone runtime:

1. **`source/dllmain.cpp` & `PluginBase.cpp`**:
   * *Role*: Windows DLL entry point (`DllMain`), handling `DLL_PROCESS_ATTACH` and `DLL_PROCESS_DETACH`.
   * *Replacement*: Standard cross-platform `int main(int argc, char** argv)` application runner.
2. **`source/reversiblehooks/` (ReversibleHooks Engine)**:
   * *Role*: Manages 7,002 hooks, allocates detour trampolines, writes x86 JMP instructions to memory, and inspects exported VMT symbols.
   * *Replacement*: In a native standalone executable, functions are linked directly at compile/link time. The entire hooking engine is obsolete and removed from the critical execution path.
3. **RenderWare Dummy Implementation Layer (`source/game_sa/RenderWare/rw/`)**:
   * *Role*: Bridge between GTA code and `gta_sa.exe` RenderWare binary.
   * *Replacement*: Real RenderWare Graphics engine (such as `librw`).
4. **Win32 Platform Scaffolding (`source/app/platform/win/WinPs.cpp`, `WndProc.cpp`)**:
   * *Role*: Legacy Windows message pump, DirectInput mouse hooks, and display mode dialogs.
   * *Replacement*: Unified SDL3 platform abstraction backend (`SDL_CreateWindow`, `SDL_PollEvent`).
