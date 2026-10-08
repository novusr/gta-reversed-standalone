# Phase 4: Stub Unreversed Functions & Eliminate plugin::Call

* **Status**: **COMPLETED**
* **Prerequisites**: Phase 1 (`StaticRef` & Storage Decoupling), Phase 2 (PAL), Phase 3 (VFS Normalization).

---

## 1. Objective
Eliminate fatal segmentation faults (Access Violation `0xC0000005` / `SIGSEGV`) caused by calls to unmapped retail `gta_sa.exe` virtual addresses by classifying all active `plugin::Call` occurrences and providing a safe, non-crashing diagnostic stub framework alongside core subsystem stubs (`Interior_c`, `InteriorGroup_c`, and `CMemoryMgr`).

---

## 2. Implementation Summary

### 1. Diagnostic Stub Framework (`source/PluginBase.h` & `source/PluginBase.cpp`)
- Guarded `plugin::Call`, `plugin::CallAndReturn`, `plugin::CallMethod`, `plugin::CallMethodAndReturn`, `plugin::CallVirtualMethod`, and `plugin::CallVirtualMethodAndReturn` under `#ifdef NOTSA_STANDALONE_NATIVE`.
- Implemented `detail::SafeDefault<Ret>()` supporting:
  - Reference return types (via aligned static dummy bytes to avoid invalid reference initialization errors)
  - Pointers (`nullptr`)
  - Arithmetic/primitives and enums (`0`, `0.0f`, `false`)
  - Value structs (`CVector{0, 0, 0}`, `CRect`, etc.)
- Integrated rate-limited `NOTSA_LOG_WARN` logging (logged once per call site address to prevent console performance flooding during 60 FPS update loops).
- Isolated `GetBaseAddress()` and `GetGlobalAddress()` in `source/PluginBase.cpp` so they do not depend on Win32 API `GetModuleHandleA` in standalone native mode.

### 2. Core Subsystem Fallbacks
- **`CMemoryMgr` (`source/game_sa/MemoryMgr.cpp`)**:
  - Decoupled `InitScratchPad` and `MallocAlign` to native heap functions under `NOTSA_STANDALONE_NATIVE`.
- **`InteriorGroup_c` (`source/game_sa/Interior/InteriorGroup_c.cpp`)**:
  - Implemented native `Init`, `AddInterior`, `Exit`, `GetEntity`, and `GetPed` to maintain valid interior lists during building/room traversal without depending on unmapped retail routines.
- **`Interior_c` (`source/game_sa/Interior/Interior_c.cpp`)**:
  - Implemented native `Init`, `Exit`, and `IsPtInside` fallback routines.

### 3. Audit & Subsystem Classification
- Extracted and classified all `plugin::Call` sites into [docs/standalone/audits/PLUGIN_CALL_AUDIT.md](file:///home/novusr/Desktop/gta-reversed/docs/standalone/audits/PLUGIN_CALL_AUDIT.md).
- Subsystem breakdown:
  - Pedestrians & Tasks: 229 calls
  - Vehicles & Traffic AI: 189 calls
  - Interiors & Furniture: 73 calls
  - Rendering & Special FX: 55 calls
  - Audio System: 40 calls
  - Camera Subsystem: 24 calls
  - Scripting & SCM: 24 calls
  - UI & Frontend: 15 calls
  - Memory & Platform: 12 calls
  - Collision & World Geometry: 8 calls
  - Miscellaneous: 136 calls

---

## 3. Verification Protocol
- [x] Standalone build compiles without raw function pointer calls to `0x00...`.
- [x] Triggering an unreversed routine logs a formatted warning (`NOTSA_LOG_WARN`) instead of crashing the process.
- [x] Verified via standalone C++23 test harness (`scratch/test_plugin_base.cpp`):
  - `plugin::Call`: Logs warning once; does not crash on repeated calls.
  - `plugin::CallAndReturn<int>`: Returns 0.
  - `plugin::CallAndReturn<bool>`: Returns false.
  - `plugin::CallAndReturn<void*>`: Returns `nullptr`.
  - `plugin::CallMethodAndReturn<DummyStruct>`: Safely returns default struct.
  - `plugin::CallMethodAndReturn<DummyClass&>`: Safely resolves reference return types without memory faults.
  - `GetGlobalAddress` / `GetBaseAddress`: Portable standalone resolution.
- [x] Dual-mode compatibility preserved for retail ASI builds (`#ifndef NOTSA_STANDALONE_NATIVE`).

