#include <StdInc.h>

#ifdef NOTSA_USE_SDL3
#include <SDL3/SDL.h>

bool CPad::ProcessMouseEvent(const SDL_Event& e, CMouseControllerState& ms) {
    switch (e.type) {
    case SDL_EVENT_MOUSE_BUTTON_DOWN:
    case SDL_EVENT_MOUSE_BUTTON_UP: {
        switch (e.button.button) {
        case SDL_BUTTON_LEFT:   ms.isMouseLeftButtonPressed = e.button.down;  break;
        case SDL_BUTTON_RIGHT:  ms.isMouseRightButtonPressed = e.button.down;  break;
        case SDL_BUTTON_MIDDLE: ms.isMouseMiddleButtonPressed = e.button.down;  break;
        case SDL_BUTTON_X1:     ms.isMouseFirstXPressed = e.button.down; break;
        case SDL_BUTTON_X2:     ms.isMouseSecondXPressed = e.button.down; break;
        }
        return true;
    }
    case SDL_EVENT_MOUSE_WHEEL: {
        ms.isMouseWheelMovedUp   = e.wheel.y > 0.f;
        ms.isMouseWheelMovedDown = e.wheel.y < 0.f;
        return true;
    }
    case SDL_EVENT_MOUSE_MOTION: {
        ms.m_AmountMoved.x += e.motion.xrel;
        ms.m_AmountMoved.y += e.motion.yrel;
        return true;
    }
    case SDL_EVENT_MOUSE_ADDED:
    case SDL_EVENT_MOUSE_REMOVED: {
        NOTSA_LOG_DEBUG(
            "SDL: Mouse ({}) {}",
            e.mdevice.which,
            e.mdevice.type == SDL_EVENT_MOUSE_ADDED ? "added" : "removed"
        );
        return true;
    }
    }
    return false;
}

bool CPad::ProcessKeyboardEvent(const SDL_Event& e, CKeyboardState& ks) {
    switch (e.type) {
    case SDL_EVENT_KEY_DOWN:
    case SDL_EVENT_KEY_UP: {
        if (e.key.repeat) {
            return true;
        }

        //NOTSA_LOG_DEBUG("SDL: Key ({}): {}", (char)(e.key.key), e.key.down);

        const auto s = e.key.down ? 255 : 0;

        // Keypad doesn't have individual key values in SDL3
        switch (e.key.scancode) { 
        case SDL_SCANCODE_KP_0: ks.num0 = s; return true;
        case SDL_SCANCODE_KP_1: ks.num1 = s; return true;
        case SDL_SCANCODE_KP_2: ks.num2 = s; return true;
        case SDL_SCANCODE_KP_3: ks.num3 = s; return true;
        case SDL_SCANCODE_KP_4: ks.num4 = s; return true;
        case SDL_SCANCODE_KP_5: ks.num5 = s; return true;
        case SDL_SCANCODE_KP_6: ks.num6 = s; return true;
        case SDL_SCANCODE_KP_7: ks.num7 = s; return true;
        case SDL_SCANCODE_KP_8: ks.num8 = s; return true;
        case SDL_SCANCODE_KP_9: ks.num9 = s; return true;
        }

        switch (e.key.key) {
        case SDLK_F1:           ks.FKeys[0] = s;                break;                     
        case SDLK_F2:           ks.FKeys[1] = s;                break;                     
        case SDLK_F3:           ks.FKeys[2] = s;                break;                     
        case SDLK_F4:           ks.FKeys[3] = s;                break;                     
        case SDLK_F5:           ks.FKeys[4] = s;                break;                     
        case SDLK_F6:           ks.FKeys[5] = s;                break;                     
        case SDLK_F7:           ks.FKeys[6] = s;                break;                     
        case SDLK_F8:           ks.FKeys[7] = s;                break;                     
        case SDLK_F9:           ks.FKeys[8] = s;                break;                     
        case SDLK_F10:          ks.FKeys[9] = s;                break;                    
        case SDLK_F11:          ks.FKeys[10] = s;               break;                    
        case SDLK_F12:          ks.FKeys[11] = s;               break;
        case SDLK_ESCAPE:       ks.esc = s;                     break;
        case SDLK_INSERT:       ks.insert = s;                  break;
        case SDLK_DELETE:       ks.del = s;                     break;
        case SDLK_HOME:         ks.home = s;                    break;
        case SDLK_END:          ks.end = s;                     break;
        case SDLK_PAGEUP:       ks.pgup = s;                    break;
        case SDLK_PAGEDOWN:     ks.pgdn = s;                    break;
        case SDLK_UP:           ks.up = s;                      break; // Arrow up
        case SDLK_DOWN:         ks.down = s;                    break; // Arrow down
        case SDLK_LEFT:         ks.left = s;                    break; // Arrow left
        case SDLK_RIGHT:        ks.right = s;                   break; // Arrow right
        case SDLK_SCROLLLOCK:   ks.scroll = s;                  break;
        case SDLK_PAUSE:        ks.pause = s;                   break;
        case SDLK_NUMLOCKCLEAR: ks.numlock = s;                 break; // (?)
        case SDLK_SLASH:        ks.div = s;                     break;
        case SDLK_ASTERISK:     ks.mul = s;                     break;
        case SDLK_MINUS:        ks.sub = s;                     break;
        case SDLK_PLUS:         ks.add = s;                     break;
        case SDLK_RETURN:       ks.enter = s;                   break;
        case SDLK_PERIOD:       ks.decimal = s;                 break;
        case SDLK_TAB:          ks.tab = s;                     break;
        case SDLK_CAPSLOCK:     ks.capslock = s;                break;
        case SDLK_KP_ENTER:     ks.extenter = s;                break; // (?)
        case SDLK_LSHIFT:       ks.lshift = s;                  break;
        case SDLK_RSHIFT:       ks.rshift = s;                  break;
        case SDLK_LCTRL:        ks.lctrl = s;                   break;
        case SDLK_RCTRL:        ks.rctrl = s;                   break;
        case SDLK_LALT:         ks.lalt = s;                    break;
        case SDLK_RALT:         ks.ralt = s;                    break;
        case SDLK_LGUI:         ks.lwin = s;                    break;
        case SDLK_RGUI:         ks.rwin = s;                    break;
        case SDLK_APPLICATION:  ks.apps = s;                    break; // (?)
        default: { // Other keys
            const auto key = std::toupper(e.key.key);
            if (key <= 0xFF) {
                ks.standardKeys[key] = s;
            }
            return true;
        }
        }
        ks.shift = (ks.rshift || ks.lshift) ? 255 : 0;
        return true;
    }
    case SDL_EVENT_KEYBOARD_ADDED:
    case SDL_EVENT_KEYBOARD_REMOVED: {
        NOTSA_LOG_DEBUG(
            "SDL: Keyboard ({}) {}",
            e.kdevice.which,
            e.kdevice.type == SDL_EVENT_KEYBOARD_ADDED ? "added" : "removed"
        );
        return true;
    }
    }
    return false;
}

static SDL_Gamepad* s_Gamepads[2]{ nullptr, nullptr };
static SDL_JoystickID s_GamepadIDs[2]{ 0, 0 };

static int GetPadIndexForGamepadID(SDL_JoystickID id) {
    if (s_GamepadIDs[0] == id) return 0;
    if (s_GamepadIDs[1] == id) return 1;
    if (s_GamepadIDs[0] == 0) { s_GamepadIDs[0] = id; return 0; }
    if (s_GamepadIDs[1] == 0) { s_GamepadIDs[1] = id; return 1; }
    return 0;
}

bool CPad::ProcessGamepadEvent(const SDL_Event& e, CControllerState& cs) {
    switch (e.type) {
    case SDL_EVENT_GAMEPAD_BUTTON_DOWN:
    case SDL_EVENT_GAMEPAD_BUTTON_UP: {
        const int16 state = (e.type == SDL_EVENT_GAMEPAD_BUTTON_DOWN) ? 255 : 0;
        switch (e.gbutton.button) {
        case SDL_GAMEPAD_BUTTON_SOUTH:          cs.ButtonCross = state; break;
        case SDL_GAMEPAD_BUTTON_EAST:           cs.ButtonCircle = state; break;
        case SDL_GAMEPAD_BUTTON_WEST:           cs.ButtonSquare = state; break;
        case SDL_GAMEPAD_BUTTON_NORTH:          cs.ButtonTriangle = state; break;
        case SDL_GAMEPAD_BUTTON_LEFT_SHOULDER:  cs.LeftShoulder1 = state; break;
        case SDL_GAMEPAD_BUTTON_RIGHT_SHOULDER: cs.RightShoulder1 = state; break;
        case SDL_GAMEPAD_BUTTON_START:          cs.Start = state; break;
        case SDL_GAMEPAD_BUTTON_BACK:           cs.Select = state; break;
        case SDL_GAMEPAD_BUTTON_LEFT_STICK:     cs.ShockButtonL = state; break;
        case SDL_GAMEPAD_BUTTON_RIGHT_STICK:    cs.ShockButtonR = state; break;
        case SDL_GAMEPAD_BUTTON_DPAD_UP:        cs.DPadUp = state; break;
        case SDL_GAMEPAD_BUTTON_DPAD_DOWN:      cs.DPadDown = state; break;
        case SDL_GAMEPAD_BUTTON_DPAD_LEFT:      cs.DPadLeft = state; break;
        case SDL_GAMEPAD_BUTTON_DPAD_RIGHT:     cs.DPadRight = state; break;
        default: return false;
        }
        return true;
    }
    case SDL_EVENT_GAMEPAD_AXIS_MOTION: {
        constexpr int16 DEADZONE = 6500; // ~20% analog deadzone
        const auto ApplyDeadzone = [DEADZONE](int16 value) -> int16 {
            if (std::abs(value) <= DEADZONE) {
                return 0;
            }
            float normalized = (float)value / 32767.0f;
            return static_cast<int16>(std::clamp(normalized * 128.0f, -128.0f, 127.0f));
        };

        switch (e.gaxis.axis) {
        case SDL_GAMEPAD_AXIS_LEFTX: {
            int16 val = ApplyDeadzone(e.gaxis.value);
            if (FrontEndMenuManager.m_bInvertPadX1) val = -val;
            (FrontEndMenuManager.m_bSwapPadAxis1 ? cs.LeftStickY : cs.LeftStickX) = val;
            return true;
        }
        case SDL_GAMEPAD_AXIS_LEFTY: {
            int16 val = ApplyDeadzone(e.gaxis.value);
            if (FrontEndMenuManager.m_bInvertPadY1) val = -val;
            (FrontEndMenuManager.m_bSwapPadAxis1 ? cs.LeftStickX : cs.LeftStickY) = val;
            return true;
        }
        case SDL_GAMEPAD_AXIS_RIGHTX: {
            int16 val = ApplyDeadzone(e.gaxis.value);
            if (FrontEndMenuManager.m_bInvertPadX2) val = -val;
            (FrontEndMenuManager.m_bSwapPadAxis2 ? cs.RightStickY : cs.RightStickX) = val;
            return true;
        }
        case SDL_GAMEPAD_AXIS_RIGHTY: {
            int16 val = ApplyDeadzone(e.gaxis.value);
            if (FrontEndMenuManager.m_bInvertPadY2) val = -val;
            (FrontEndMenuManager.m_bSwapPadAxis2 ? cs.RightStickX : cs.RightStickY) = val;
            return true;
        }
        case SDL_GAMEPAD_AXIS_LEFT_TRIGGER: {
            cs.LeftShoulder2 = static_cast<int16>((std::max<int16>(0, e.gaxis.value) / 32767.0f) * 255.0f);
            return true;
        }
        case SDL_GAMEPAD_AXIS_RIGHT_TRIGGER: {
            cs.RightShoulder2 = static_cast<int16>((std::max<int16>(0, e.gaxis.value) / 32767.0f) * 255.0f);
            return true;
        }
        default: return false;
        }
    }
    }
    return false;
}

bool CPad::ProcessJoyStickEvent(const SDL_Event& e, CControllerState& cs) {
    return false;
}

void CPad::UpdateGamepadVibration() {
    for (size_t i = 0; i < std::size(Pads); i++) {
        if (i >= 2 || !s_Gamepads[i]) {
            continue;
        }
        auto* pad = GetPad((int32)i);
        if (FrontEndMenuManager.m_PrefsUseVibration && pad->ShakeDur > 0 && pad->ShakeFreq > 0) {
            Uint16 intensity = static_cast<Uint16>(std::min(65535, (int)pad->ShakeFreq * 257));
            SDL_RumbleGamepad(s_Gamepads[i], intensity, intensity, static_cast<Uint32>(pad->ShakeDur));
        } else {
            SDL_RumbleGamepad(s_Gamepads[i], 0, 0, 0);
        }
    }
}

bool CPad::ProcessEvent(const SDL_Event& e, bool ignoreMouseEvents, bool ignoreKeyboardEvents) {
    // Mouse/keyboard events are meant to be handled by Pad 0
    if (!ignoreMouseEvents && GetPad(0)->ProcessMouseEvent(e, TempMouseControllerState)) {
        return true;
    }
    if (!ignoreKeyboardEvents && GetPad(0)->ProcessKeyboardEvent(e, TempKeyState)) {
        return true;
    }

    if (e.type == SDL_EVENT_GAMEPAD_ADDED) {
        const auto id = e.gdevice.which;
        for (int i = 0; i < 2; ++i) {
            if (!s_Gamepads[i]) {
                s_Gamepads[i] = SDL_OpenGamepad(id);
                s_GamepadIDs[i] = id;
                NOTSA_LOG_INFO("SDL: Gamepad connected for Pad {}: {}", i, SDL_GetGamepadName(s_Gamepads[i]));
                break;
            }
        }
        return true;
    }

    if (e.type == SDL_EVENT_GAMEPAD_REMOVED) {
        const auto id = e.gdevice.which;
        for (int i = 0; i < 2; ++i) {
            if (s_GamepadIDs[i] == id) {
                if (s_Gamepads[i]) {
                    SDL_CloseGamepad(s_Gamepads[i]);
                    s_Gamepads[i] = nullptr;
                }
                s_GamepadIDs[i] = 0;
                NOTSA_LOG_INFO("SDL: Gamepad disconnected for Pad {}", i);
                break;
            }
        }
        return true;
    }

    if (e.type == SDL_EVENT_GAMEPAD_BUTTON_DOWN || e.type == SDL_EVENT_GAMEPAD_BUTTON_UP || e.type == SDL_EVENT_GAMEPAD_AXIS_MOTION) {
        SDL_JoystickID id = (e.type == SDL_EVENT_GAMEPAD_AXIS_MOTION) ? e.gaxis.which : e.gbutton.which;
        int padIdx = GetPadIndexForGamepadID(id);
        if (padIdx >= 0 && padIdx < 2) {
            return GetPad(padIdx)->ProcessGamepadEvent(e, GetPad(padIdx)->PCTempJoyState);
        }
    }

    // Other events can be handled by any pad
    for (auto& pad : Pads) {
        if (pad.ProcessJoyStickEvent(e, pad.PCTempJoyState)) {
            return true;
        }
    }

    // Event not processed
    return false;
}
#endif
