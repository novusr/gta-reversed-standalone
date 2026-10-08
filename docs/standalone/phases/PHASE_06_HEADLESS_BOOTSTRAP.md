# Phase 6: Headless Engine Bootstrap

* **Status**: **PLANNED**
* **Prerequisites**: Phase 1 (`StaticRef`), Phase 4 (Stubs), Phase 5 (`librw`).

---

## 1. Objective
Boot the complete core engine simulation without requiring an active graphical window, validating memory allocation stability, entity pool creation, and math systems.

---

## 2. Scope & Key Tasks
1. **Author Standalone Main**:
   - Implement `source/app/Main.cpp` as the primary entry point for `NOTSA_STANDALONE_NATIVE`.
   - Initialize logging, parse command-line arguments, and set up crash handlers.
2. **Sequential Pre-Render Initialization**:
   - Execute `CMemoryMgr::Init()`.
   - Execute `CLocalisation::Initialise()`.
   - Execute `CFileMgr::Initialise()`.
   - Execute `CPools::Initialise()` (verifying all entity and task pools).
   - Execute `CGame::InitialiseOnceBeforeRW()`.
3. **Headless Execution Verification**:
   - Run a 1,000-tick headless update loop and verify zero memory leaks or crashes.

---

## 3. Verification Protocol
- [ ] Executable boots, allocates pools, processes initial ticks, and exits with code 0.
- [ ] AddressSanitizer (ASan) reports zero access violations or uninitialized reads during bootstrap.
