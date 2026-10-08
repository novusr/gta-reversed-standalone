# RenderWare Architecture & librw Migration Analysis: GTA Reversed

RenderWare Graphics is the central rendering, scene graph, and resource framework of Grand Theft Auto: San Andreas. Understanding how RenderWare is currently handled in `gta-reversed` is critical to evaluating the feasibility of a standalone runtime.

---

## 1. Current State of RenderWare in GTA Reversed

### 1.1 Does GTA Reversed Currently Use the Original RenderWare Binary?
**YES, 100%.** GTA Reversed contains **NO** implementation of the RenderWare graphics engine.
* The header files under `source/game_sa/RenderWare/rw/` (`rwcore.h`, `rpworld.h`, `rpskin.h`, `rphanim.h`, `rpmatfx.h`, `rtanim.h`, etc.) are C API declarations originally derived from Criterion Software's RenderWare SDK 3.6 / 3.7 and DK22Pac's `plugin-sdk`.
* The corresponding implementation files (`rwcore.cpp`, `rpworld.cpp`, `rwplcore.cpp`, `rpskin.cpp`, `rphanim.cpp`) contain **1,377 hardcoded address trampolines** forwarding every API call directly to the machine code inside `gta_sa.exe`.

#### Concrete Evidence from Source Code:
From `source/game_sa/RenderWare/rw/rwplcore.cpp:325-343`:
```cpp
RwBool RwEngineOpen(RwEngineOpenParams* initParams) {
    return ((RwBool(__cdecl *)(RwEngineOpenParams*))0x7F2F70)(initParams);
}

RwBool RwEngineStart() {
    return ((RwBool(__cdecl *)(void))0x7F2E70)();
}

RwBool RwEngineStop() {
    return ((RwBool(__cdecl *)(void))0x7F2E20)();
}

RwBool RwEngineClose() {
    return ((RwBool(__cdecl *)(void))0x7F2F00)();
}
```

From `source/game_sa/RenderWare/rw/rwcore.cpp:15-37`:
```cpp
RxHeap* RxHeapCreate(RwUInt32 size) {
    return ((RxHeap*(__cdecl *)(RwUInt32))0x809F90)(size);
}

void* RxHeapAlloc(RxHeap* heap, RwUInt32 size) {
    return ((void*(__cdecl *)(RxHeap*, RwUInt32))0x809AA0)(heap, size);
}
```

From `source/game_sa/RenderWare/rw/rpworld.cpp:6-8`:
```cpp
void _rwD3D9VSSetActiveWorldMatrix(const RwMatrix* worldMatrix) {
    ((void(__cdecl *)(const RwMatrix*))0x764650)(worldMatrix);
}
```

From `source/game_sa/RenderWare/RenderWare.h:22-31`:
```cpp
static inline auto& RwInitialized    = StaticRef<bool>(0xC920E8);
static inline auto& RwEngineInstance = StaticRef<RwGlobals*>(0xC97B24);
static inline auto& RsGlobal         = StaticRef<RsGlobalType>(0xC17040);
static inline auto& geometryTKList   = StaticRef<RwPluginRegistry>(0x8D628C);

inline IDirect3DDevice9* GetD3D9Device() {
    return *reinterpret_cast<IDirect3DDevice9 **>(0xC97C28);
}
```

---

## 2. RenderWare Coupling with Game Classes

The game engine is **extremely tightly coupled** to RenderWare data structures. Rather than abstracting RenderWare behind a modern rendering interface, the original game architecture embedded RenderWare pointers directly into core gameplay objects:

```
                  ┌──────────────────────┐
                  │      CPlaceable      │
                  │  (Matrix, Position)  │
                  └──────────▲───────────┘
                             │
                  ┌──────────┴───────────┐
                  │       CEntity        │
                  │  RwObject* m_pRwObj  │◄────────┐
                  └──────────▲───────────┘         │
                             │                     │
                  ┌──────────┴───────────┐         │
                  │      CPhysical       │         │ (Downcasted to
                  │   (Forces, Velocity) │         │  RpAtomic* or RpClump*)
                  └──────────▲───────────┘         │
                             │                     │
              ┌──────────────┴──────────────┐      │
              │                             │      │
     ┌────────┴────────┐           ┌────────┴──────┴─┐
     │      CPed       │           │     CVehicle    │
     │ RpHAnimHierarchy│           │ Vehicle Clump   │
     │ Bone Transforms │           │ Dummy Frames    │
     └─────────────────┘           └─────────────────┘
```

### Detailed Class-to-RenderWare Association:
1. **`CEntity` (`source/game_sa/Entity/Entity.h:51`)**:
   * Stores `RwObject* m_pRwObject;`.
   * For static buildings, trees, and small props, `m_pRwObject` points to an `RpAtomic*`.
   * For peds, vehicles, and animated objects, `m_pRwObject` points to an `RpClump*`.
   * Directly queries RenderWare transforms: `RwFrame* frame = (RwFrame*)rwObjectGetParent(m_pRwObject)`.
2. **`CPed` (`source/game_sa/Entity/Ped/Ped.h`)**:
   * Holds `RpHAnimHierarchy*` (hierarchical skeletal bone hierarchy).
   * Animation blending updates `RpHAnimHierarchy::pNodeInfo` matrices directly.
3. **`CVehicle` (`source/game_sa/Entity/Vehicle/Vehicle.h`)**:
   * Hierarchical clump with named `RwFrame` nodes (`wheel_rf`, `wheel_lf`, `door_rf`, `bonnet`, `boot`, `exhaust`, `ped_frontseat`).
   * Component deformation, door swinging, and wheel rotation manipulate the matrix of the corresponding `RwFrame`.
4. **`CBaseModelInfo` & `CClumpModelInfo` (`source/game_sa/Models/`)**:
   * Holds `RpClump* m_pClump` or `RpAtomic* m_pAtomic` loaded directly from `.dff` files.
5. **`CTxdStore` (`source/game_sa/TxdStore.cpp`)**:
   * Holds `RwTexDictionary*` dictionaries containing `RwTexture*` loaded from `.txd` files.
6. **`CStreaming::ConvertBufferToObject` (`source/game_sa/Streaming.cpp:427`)**:
   * Directly feeds raw memory buffers into `RpClumpStreamRead(stream)` and `RtDictSchemaStreamReadDict`.

---

## 3. Render Dispatch Chain

When the game renders a frame, execution flows through the following hierarchy:

```
CGame::Process() / Idle()
   │
   ▼
DoRWStuffStartOfFrame() (source/app/app.cpp:46)
   │
   ├─► CameraSize(Scene.m_pRwCamera, ...)
   ├─► CVisibilityPlugins::SetRenderWareCamera(Scene.m_pRwCamera)
   ├─► RwCameraClear(Scene.m_pRwCamera, ...)
   └─► RsCameraBeginUpdate(Scene.m_pRwCamera)
         │
         ▼
CRenderer::ConstructRenderList() (source/game_sa/Renderer.cpp)
   │ (Frustum culling across CWorld sectors)
   │
   ▼
CRenderer::RenderEverythingBarRoads()
   │
   ├─► CEntity::Render() (source/game_sa/Entity/Entity.cpp:638)
   │     │
   │     ├─► If Atomic: RpAtomicRender(GetRpAtomic())
   │     │     │
   │     │     ▼
   │     │   RxPipelineExecute(atomic->pipeline)
   │     │     │ (CustomBuildingDNPipeline or standard D3D9 pipeline)
   │     │     ▼
   │     │   Direct3D9 DrawIndexedPrimitive()
   │     │
   │     └─► If Clump: RpClumpRender(GetRpClump())
   │           │
   │           ▼
   │         RpClumpForAllAtomics(clump, AtomicRenderCallback)
   │
   ├─► CPostEffects::Render() (Color grading, heat haze, speed blur)
   ├─► CShadows::Render() / CRealTimeShadowManager::Update()
   └─► CHud::Draw() / CMenuManager::Draw() (CSprite2d, CFont)
         │
         ▼
DoRWStuffEndOfFrame() (source/app/app.cpp:86)
   │
   ├─► RwCameraEndUpdate(Scene.m_pRwCamera)
   └─► RsCameraShowRaster(Scene.m_pRwCamera) ──► D3D9 Present()
```

---

## 4. Analysis of `librw` as Replacement Engine

### 4.1 What is `librw`?
`librw` is an open-source, clean-room C++ reimplementation of the RenderWare Graphics 3.x engine, originally created by the `re3` (GTA III) and `reVC` (GTA Vice City) development teams. It provides exact API-level compatibility with RenderWare's public headers while supporting modern rendering backends:
* DirectX 9 (D3D9)
* OpenGL 3.3 Core / OpenGL ES 2.0 / 3.0
* DirectX 11 / Modern D3D
* WebGL / PS2 / Xbox emulation layers

### 4.2 Interfaces That Can Remain Unchanged
Because `librw` mirrors the RenderWare 3.6 API, the vast majority of calls throughout GTA Reversed's gameplay code can link **directly** against `librw` with identical syntax:
* **Core Types**: `RwV2d`, `RwV3d`, `RwMatrix`, `RwBBox`, `RwRGBA`, `RwRGBAReal`.
* **Camera & Raster**: `RwCameraCreate`, `RwCameraDestroy`, `RwCameraSetRaster`, `RwRasterCreate`, `RwRasterLock`, `RwRasterUnlock`.
* **Stream I/O**: `RwStreamOpen`, `RwStreamClose`, `RwStreamRead`, `RwStreamFindChunk`, `RpClumpStreamRead`, `RpAtomicStreamRead`.
* **Scene Graph**: `RwFrameCreate`, `RwFrameTranslate`, `RwFrameRotate`, `RwFrameAddChild`, `RpWorldAddCamera`, `RpWorldAddLight`.
* **Standard Plugins**: `rphanim` (`RpHAnimHierarchyCreate`, `RpHAnimHierarchyUpdateMatrices`), `rpmatfx` (material effects), `rpskin` (skinning matrices), `rtanim`.

### 4.3 Systems Requiring Adaptation or Custom Extension in `librw`
GTA San Andreas significantly upgraded its rendering engine compared to GTA III and Vice City. The following SA-specific subsystems are **not** present in vanilla `librw` and will require custom pipelines or adaptation layers:

1. **Custom Building Pipeline (`CustomBuildingDNPipeline`)**:
   * *Purpose*: San Andreas interpolates daytime and nighttime vertex colors on buildings and ambient geometry based on the in-game clock (`CTimeCycle`).
   * *Requirement*: Custom vertex shader and pipeline hook in `librw` binding dual vertex color streams.
2. **Custom Car Environment Map Pipeline (`CustomCarEnvMapPipeline`)**:
   * *Purpose*: Dual-layer car paint shading, specular highlight calculation, dynamic spherical reflection mapping, and damage scratch rendering.
   * *Requirement*: Custom vehicle pixel/vertex shader within `librw`.
3. **`D3DResourceSystem` Streaming Buffering**:
   * *Purpose*: GTA SA bypasses RenderWare's high-level texture loader for streaming models, streaming raw D3D texture surfaces directly into device memory (`source/game_sa/RenderWare/D3DResourceSystem.cpp`).
   * *Requirement*: An adapter layer allowing asynchronous texture buffer hydration directly into `librw::Raster`.
4. **Real-Time Shadow Manager (`CRealTimeShadowManager`)**:
   * *Purpose*: Dynamic pedestrian and vehicle shadows rendered from a directional light camera into a render-target raster, then projected onto world geometry.
   * *Requirement*: Shadow camera raster binding and projective texture matrix setup in `librw`.
5. **Procedural Foliage & Grass (`CPlantMgr`, `CGrassRenderer`)**:
   * *Purpose*: Dynamic procedural grass billboard generation around the camera with wind wave animation.
   * *Requirement*: Dynamic vertex buffer updates in `librw`.
