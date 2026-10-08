# Phase 2: Platform Abstraction Layer (SDL3 & OpenAL)

* **Status**: **COMPLETED**
* **Prerequisites**: Phase 1 (`StaticRef` & Storage Decoupling).

---

## 1. Objective
Decouple the engine lifecycle, windowing, message loop, input, and audio systems from legacy Windows Win32, DirectInput, and DirectSound APIs, establishing a clean SDL3 and OpenAL-Soft cross-platform foundation.

---

## 2. Scope & Key Tasks
1. **Windowing & Application Lifecycle**:
   - Refactor `source/app/platform/` to utilize SDL3 as the primary platform runner.
   - Replace Win32 `HWND`, `WndProc`, and `PeekMessage` loops with `SDL_CreateWindow`, `SDL_PollEvent`, and SDL display event handling in `WinMain.cpp` and `SDLWrapper.cpp`.
2. **Input Processing**:
   - Route keyboard, mouse, and game controllers from SDL3 events into `CPad` (`source/game_sa/Pad_SDL.cpp`).
   - Support modern gamepad vibration (`SDL_RumbleGamepad`) and analog stick deadzones (~20%) natively.
3. **Audio Backend**:
   - Make `NOTSA_WITH_OPENAL` and `USE_OPENAL` the default audio driver for standalone builds.
   - Verify and fix `source/game_sa/Audio/OpenAL/` classes (`OALBase`, `OALBuffer`, `OALSource`).
   - Bypass DirectSound COM dependencies in standalone builds (`DirectSoundCreate8`, `InitDirectSoundListener`, `Query3DSoundEffects`).

---

## 3. Verification Protocol
- [x] Compiles cleanly with standalone options (`GTASA_STANDALONE_NATIVE=ON` auto-enables SDL3 and OpenAL).
- [x] Opens an SDL3 window and pumps events without Win32 calls (`SDL_CreateWindow`, `SDL_PollEvent`).
- [x] OpenAL device context initializes without errors (`alcOpenDevice`, `alcCreateContext`, `alcMakeContextCurrent`).
- [x] Dual-mode compatibility preserved for vanilla ASI target (`gta_reversed.asi`).
