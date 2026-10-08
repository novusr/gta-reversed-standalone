# Phase 7: Window Creation & Basic Renderer Boot

* **Status**: **PLANNED**
* **Prerequisites**: Phase 2 (SDL3), Phase 5 (`librw`), Phase 6 (Bootstrap).

---

## 1. Objective
Open an OS window, clear the camera raster, and render 2D loading and splash screens through `librw`.

---

## 2. Scope & Key Tasks
1. **Window-to-Renderer Binding**:
   - Attach the SDL3 native window handle to `librw`'s graphics device context.
   - Configure raster dimensions, color depth, and vsync.
2. **Frame Lifecycle Pipeline**:
   - Implement `DoRWStuffStartOfFrame()`, `RwCameraClear()`, `DoRWStuffEndOfFrame()`, and `RsCameraShowRaster()`.
3. **2D Rendering & Loading Screens**:
   - Render logo splash screens (`LOADSCS.TXD`).
   - Run `CLoadingScreen::Render()` to display the animated loading bar while assets load.
   - Bind ImGui overlay to the SDL3 + `librw` pipeline.

---

## 3. Verification Protocol
- [ ] OS window opens at the configured resolution (e.g. 1920x1080).
- [ ] Screen renders clear colors and cycles splash screens without crashing or flickering.
