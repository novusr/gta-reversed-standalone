# Phase 2: Platform Abstraction Layer (SDL3 & OpenAL)

* **Status**: **PLANNED**
* **Prerequisites**: Phase 1 (`StaticRef` & Storage Decoupling).

---

## 1. Objective
Decouple the engine lifecycle, windowing, message loop, input, and audio systems from legacy Windows Win32, DirectInput, and DirectSound APIs, establishing a clean SDL3 and OpenAL-Soft cross-platform foundation.

---

## 2. Scope & Key Tasks
1. **Windowing & Application Lifecycle**:
   - Refactor `source/app/platform/` to utilize SDL3 as the primary platform runner.
   - Replace Win32 `HWND`, `WndProc`, and `PeekMessage` loops with `SDL_CreateWindow`, `SDL_PollEvent`, and SDL display event handling.
2. **Input Processing**:
   - Route keyboard, mouse, and game controllers from SDL3 events into `CPad`.
   - Support modern gamepad vibration and analog stick deadzones natively.
3. **Audio Backend**:
   - Make `NOTSA_WITH_OPENAL` the default audio driver for standalone builds.
   - Verify `source/game_sa/Audio/OpenAL/` classes (`OALBase`, `OALBuffer`, `OALSource`).
   - Remove DirectSound dependencies in standalone builds.

---

## 3. Verification Protocol
- [ ] Compiles cleanly on Windows and Linux targets.
- [ ] Opens an SDL3 window and pumps events without Win32 calls.
- [ ] OpenAL device context initializes without errors.
