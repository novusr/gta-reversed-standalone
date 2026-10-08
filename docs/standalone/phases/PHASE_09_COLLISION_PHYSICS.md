# Phase 9: Collision & Physics Verification

* **Status**: **PLANNED**
* **Prerequisites**: Phase 6 (Headless Bootstrap), Phase 8 (Asset Streaming).

---

## 1. Objective
Activate collision detection, ground surface height determination, and Newtonian rigid-body physics calculations.

---

## 2. Scope & Key Tasks
1. **Collision Data Hydration**:
   - Load `models/coll/peds.col`, `models/coll/vehicles.col`, and `DATA/SURFACE.DAT`.
   - Populate `CColStore` and collision model pools (`CColModelPool`).
2. **Raycasting & Spatial Queries**:
   - Verify `CCollision::ProcessColModels()`.
   - Test `CWorld::FindGroundZForCoord()` across multiple map coordinate samples.
   - Test `CWorld::ProcessLineOfSight()` raycasting against static collision geometry.
3. **Rigid-Body Physics**:
   - Validate `CPhysical::ProcessPhysics()` (gravity, momentum, aerodynamic drag, friction).

---

## 3. Verification Protocol
- [ ] Ground Z lookup matches canonical values for key landmarks (Grove Street, Mount Chiliad).
- [ ] Physics tick computes correct falling velocities under gravity without floating-point errors.
