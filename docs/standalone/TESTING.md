# Testing & Verification Strategy: GTA Reversed Standalone

This document outlines the testing methodologies, validation protocols, and behavioral benchmarking standards for `gta-reversed`.

---

## 1. Testing Principles & Reporting Discipline

### 1.1 Strict Validation Status Terminology
Never report that a feature "works" if only compilation was verified. Always use exact, descriptive terminology:
* **Compiles Successfully**: The target compiled without syntax or type errors.
* **Links Successfully**: The executable/library linked all symbols without unresolved external references.
* **Starts Headless**: Process initialized memory and exited cleanly without accessing invalid pointers.
* **Runtime Behavior Validated**: The feature was executed in-game and matched expected behavior against vanilla GTA SA.
* **Runtime Validation Deferred**: State exactly why runtime validation is deferred (e.g. "Runtime validation deferred because Phase 5 RenderWare runtime is not yet active").

### 1.2 Behavioral Reference Standard
* The vanilla GTA San Andreas v1.0 executable and `gta_reversed.asi` serve as the **Golden Reference**.
* When migrating a system, any behavioral divergence must be classified:
  - **Identical**: Exact math, timing, and state transitions match.
  - **Intentional Fix**: Known vanilla bug fixed via `ReversibleBugFixes`.
  - **Known Discrepancy**: Temporary limitation documented in `BLOCKERS.md`.
  - **Regression**: Unintended deviation requiring immediate rectification.

---

## 2. Testing Levels

### Level 1: Hook Registration & Metadata Testing
* **Target**: `gta_reversed.exe --dump-hooks-to=docs/hooks.json`
* **Mechanism**: Runs hook injectors across all classes in dummy mode to verify that every hook is registered without collisions, missing symbols, or memory corruption.
* **Automation**: Validated in CI on every push via `.github/workflows/update-re-progress.yml`.

### Level 2: Headless Unit & Subsystem Tests
* **Target**: Standalone headless test runner (GoogleTest / custom test harness).
* **Scope**: Core logic that does not require a GPU or active window:
  - **Math**: `CVector`, `CMatrix`, `CQuaternion`, bounding boxes.
  - **Memory & Pools**: `CPool`, `CMemoryMgr`, allocation limits and generation indices.
  - **Collision**: `CCollision::TestSphereSphere`, `TestSphereBox`, `TestLineTriangle`.
  - **Task Decision Trees**: `CTaskManager`, task sequencing, priority resolution.
  - **SCM Bytecode**: Script opcodes, arithmetic, variable registers.

### Level 3: Dual-Mode Comparison Testing (ASI vs Standalone)
* When a subsystem is refactored for standalone compatibility:
  1. Build `gta_reversed.asi` and test in vanilla game (verify no regressions in normal gameplay).
  2. Build standalone target and verify that state matches the ASI behavior.

### Level 4: Interactive Runtime Testing
* Once rendering and windowing are active (Phase 7+):
  - Frame timing stability at 30 FPS / 60 FPS.
  - Loading screen transitions.
  - Map rendering and streaming without texture corruption.
  - Vehicle handling, ped AI, audio synchronization.

---

## 3. Debugging & Diagnostic Infrastructure

### 3.1 Console Logging (`notsa::Logging`)
* Standalone builds initialize console logging via `spdlog`.
* Log levels:
  - `NOTSA_LOG_TRACE` / `DEBUG`: Detailed per-tick subsystem info.
  - `NOTSA_LOG_INFO`: Subsystem initialization, level load milestones.
  - `NOTSA_LOG_WARN`: Invocations of unreversed stubs or fallback paths.
  - `NOTSA_LOG_ERR`: Fatal errors, missing asset files, invalid pointers.

### 3.2 Tracy Profiler
* Built-in support for Tracy profiling (`tracy/cci.20220130`).
* Used to trace streaming latency, frame pacing, physics ticks, and sector querying.

### 3.3 Reversible Bug Fixes & Flags
* Features under active testing can be isolated via `ReversibleBugFixes` to ensure changes can be toggled on or off at runtime without recompiling.
