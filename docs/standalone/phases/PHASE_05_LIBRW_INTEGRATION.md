# Phase 5: librw Integration (Core RenderWare Engine)

* **Status**: **PLANNED**
* **Prerequisites**: Phase 1 (`StaticRef`), Phase 2 (Platform Layer).

---

## 1. Objective
Integrate `librw` (open-source RenderWare 3.x reimplementation) to replace the 1,377 dummy thunks in `source/game_sa/RenderWare/rw/`, providing a fully operational graphics and asset parsing engine.

---

## 2. Scope & Key Tasks
1. **Dependency Integration**:
   - Add `librw` as a CMake subproject or Conan package.
   - Configure D3D9 / Modern OpenGL / Vulkan backends.
2. **Wrapper Thunk Replacement**:
   - Wire `source/game_sa/RenderWare/rw/` thunks directly to `librw` APIs:
     - `RwEngineInit`, `RwEngineOpen`, `RwEngineStart`.
     - `RwRasterCreate`, `RwTextureRead`.
     - `RpClumpStreamRead`, `RpAtomicClone`.
     - `RpHAnimHierarchyCreate`, `RpSkinAtomicGetHAnimHierarchy`.
3. **Custom SA Rendering Pipelines**:
   - Port San Andreas custom pipelines to `librw`:
     - `CCustomBuildingDNPipeline` (Day/Night vertex illumination blending).
     - `CCustomCarEnvMapPipeline` (Vehicle reflection and specular mapping).
     - `CCustomBuildingPipeline`.

---

## 3. Verification Protocol
- [ ] `librw` compiles and links into standalone target.
- [ ] `RwEngineInit`, `RwEngineOpen`, and `RwEngineStart` initialize successfully in a native process.
- [ ] Clump stream reading correctly parses a `.dff` model into an `RpClump*`.
