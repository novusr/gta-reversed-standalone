# Phase 4: Stub Unreversed Functions & Eliminate plugin::Call

* **Status**: **PLANNED**
* **Prerequisites**: Phase 1 (`StaticRef` & Storage Decoupling).

---

## 1. Objective
Eliminate fatal segmentation faults caused by calls to unmapped GTA.exe addresses by classifying all 838 `plugin::Call` occurrences and providing safe native stubs or implementations.

---

## 2. Scope & Key Tasks
1. **Audit & Classification**:
   - Extract and categorize all 838 `plugin::Call` call sites into:
     - **Reversed**: Methods that can now be implemented directly.
     - **Safe Stubs**: Non-critical helper functions (e.g., analytics, minor visual effects) that can log and return safe defaults (`false`, `0`, `nullptr`).
     - **Critical Gaps**: Subsystems requiring complete reversal before full gameplay can function (`Interior_c`, specific camera modes).
2. **Diagnostic Stub Framework**:
   - Update `source/PluginBase.h`:
     ```cpp
     #ifdef NOTSA_STANDALONE_NATIVE
     template <unsigned int address, typename... Args>
     void Call(Args... args) {
         NOTSA_LOG_WARN("Unreversed plugin::Call invoked at address 0x{:08X}", address);
     }
     #endif
     ```
3. **Core Subsystem Stubs**:
   - Provide minimal functional stubs for `Interior_c` so building interiors do not crash the engine during traversal.

---

## 3. Verification Protocol
- [ ] Standalone build compiles without raw function pointer calls to `0x00...`.
- [ ] Triggering an unreversed routine logs a formatted warning instead of crashing the process.
