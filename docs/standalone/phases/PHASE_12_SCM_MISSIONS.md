# Phase 12: Mission Scripting (SCM) Engine Activation

* **Status**: **PLANNED**
* **Prerequisites**: Phase 11 (Ped & Vehicle Spawning).

---

## 1. Objective
Execute original GTA San Andreas SCM bytecode (`main.scm`, `script.img`), validating mission script execution, cutscenes, mission markers, and save/load state.

---

## 2. Scope & Key Tasks
1. **SCM Virtual Machine**:
   - Load `data/script/main.scm` into native `ScriptSpace`.
   - Initialize `CTheScripts::Init()` and spawn initial mission threads (`CRunningScript`).
2. **Opcode Execution**:
   - Verify all 800+ script opcode handlers in `source/game_sa/Scripts/`.
   - Validate global and local script variable registers.
3. **Mission Lifecycle & Systems**:
   - Test cutscene streaming and playback.
   - Test mission cleanup, failure, and completion triggers.
   - Test radar blips, pickups, and HUD markers.
   - Test game save file serialization and deserialization.

---

## 3. Verification Protocol
- [ ] Intro cutscene plays sequentially.
- [ ] Opening mission ("In the Beginning" / "Big Smoke") starts, spawns bicycles, guides player, and completes cleanly.
- [ ] Save game files load and save with 100% byte compatibility.
