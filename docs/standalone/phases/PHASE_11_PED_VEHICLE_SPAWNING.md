# Phase 11: Pedestrian & Vehicle Spawning

* **Status**: **PLANNED**
* **Prerequisites**: Phase 9 (Collision/Physics), Phase 10 (World Tick).

---

## 1. Objective
Spawn the player ped, stream animations (`ANIM/PED.IFP`), instantiate ambient vehicles, and verify vehicle handling and pedestrian AI task execution.

---

## 2. Scope & Key Tasks
1. **Player Ped Spawning**:
   - Instantiate `CPlayerPed` at starting world coordinates.
   - Bind `RpHAnimHierarchy` skeletal bones and stream `PED.IFP`.
   - Connect user input from `CPad` to movement tasks (`CTaskSimpleRunAnim`, `CTaskSimplePlayerOnFoot`).
2. **Vehicle Spawning & Physics**:
   - Spawn vehicle entities (`CAutomobile`, `CBike`) from `cHandlingDataMgr` parameters.
   - Process suspension raycasts, tire contact friction, steering, and engine torque.
3. **Ambient AI & Traffic**:
   - Verify `CCarCtrl` spawning and routing traffic along road nodes (`CPathFind`).
   - Verify `CPopulation` ambient pedestrian generation and wander tasks.

---

## 3. Verification Protocol
- [ ] Player can walk, run, sprint, jump, and enter vehicles.
- [ ] Vehicle physics feels authentic and matches handling equations of retail GTA SA.
- [ ] Peds react to threats (horns, gunshots, collisions) via `CEventHandler`.
