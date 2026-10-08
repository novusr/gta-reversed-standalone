# Phase 10: World & Scene Spatial Ticking

* **Status**: **PLANNED**
* **Prerequisites**: Phase 7 (Renderer Boot), Phase 8 (Streaming), Phase 9 (Collision).

---

## 1. Objective
Populate the 120x120 sector spatial hash with map geometry from IPL files, construct render lists, and render static world geometry.

---

## 2. Scope & Key Tasks
1. **World Sector Population**:
   - Parse `IPL` (Item Placement) stream files and insert static buildings into `CWorld::ms_aSectors`.
   - Update spatial broadphase indexing.
2. **Scene Traversal & Culling**:
   - Execute `CRenderer::ConstructRenderList()`.
   - Perform camera frustum culling, distance LOD checks, and occlusion checks.
3. **Static Geometry Rendering**:
   - Render static buildings, roads, terrain, and vegetation using `librw`.
   - Apply Day/Night lighting interpolation via `CCustomBuildingDNPipeline`.

---

## 3. Verification Protocol
- [ ] 3D buildings and roads render correctly around the active camera position.
- [ ] Sector entry/exit correctly updates entity sector lists without dangling pointers.
