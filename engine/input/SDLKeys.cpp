#include "SDLKeys.h"
#include <SDL_gamecontroller.h>
#include <SDL_keycode.h>
#include <SDL_mouse.h>
#include <events/models/KeyUpEvent.h>

namespace engine {
namespace input {
    const std::map<SDL_Keycode, Keys> SDLKeys::KEYCODES = {
        { SDLK_a, Keys::A },
        { SDLK_b, Keys::B },
        { SDLK_c, Keys::C },
        { SDLK_d, Keys::D },
        { SDLK_e, Keys::E },
        { SDLK_f, Keys::F },
        { SDLK_g, Keys::G },
        { SDLK_h, Keys::H },
        { SDLK_i, Keys::I },
        { SDLK_j, Keys::J },
        { SDLK_k, Keys::K },
        { SDLK_l, Keys::L },
        { SDLK_m, Keys::M },
        { SDLK_n, Keys::N },
        { SDLK_o, Keys::O },
        { SDLK_p, Keys::P },
        { SDLK_q, Keys::Q },
        { SDLK_r, Keys::R },
        { SDLK_s, Keys::S },
        { SDLK_t, Keys::T },
        { SDLK_u, Keys::U },
        { SDLK_v, Keys::V },
        { SDLK_w, Keys::W },
        { SDLK_x, Keys::X },
        { SDLK_y, Keys::Y },
        { SDLK_z, Keys::Z },
        { SDLK_1, Keys::NUM_ONE },
        { SDLK_2, Keys::NUM_TWO },
        { SDLK_3, Keys::NUM_THREE },
        { SDLK_4, Keys::NUM_FOUR },
        { SDLK_5, Keys::NUM_FIVE },
        { SDLK_6, Keys::NUM_SIX },
        { SDLK_7, Keys::NUM_SEVEN },
        { SDLK_8, Keys::NUM_EIGHT },
        { SDLK_9, Keys::NUM_NINE },
        { SDLK_0, Keys::NUM_ZERO },
        { SDLK_LSHIFT, Keys::L_SHIFT },
        { SDLK_RSHIFT, Keys::R_SHIFT },
        { SDLK_LALT, Keys::L_ALT },
        { SDLK_RALT, Keys::R_ALT },
        { SDLK_LCTRL, Keys::L_CTRL },
        { SDLK_RCTRL, Keys::R_CTRL },
        { SDLK_LGUI, Keys::L_SUPER },
        { SDLK_RGUI, Keys::R_SUPER },
        { SDLK_SPACE, Keys::SPACE },
        { SDLK_RETURN, Keys::RETURN },
        { SDLK_RETURN2, Keys::RETURN },
        { SDLK_DELETE, Keys::BACKSPACE },
        { SDLK_BACKSPACE, Keys::BACKSPACE },
        { SDLK_KP_ENTER, Keys::RETURN },
        { SDL_CONTROLLER_BUTTON_A, Keys::CON_A },
        { SDL_CONTROLLER_BUTTON_B, Keys::CON_B },
        { SDL_CONTROLLER_BUTTON_X, Keys::CON_X },
        { SDL_CONTROLLER_BUTTON_Y, Keys::CON_Y },
        { SDL_CONTROLLER_BUTTON_DPAD_LEFT, Keys::CON_DPAD_LEFT },
        { SDL_CONTROLLER_BUTTON_DPAD_RIGHT, Keys::CON_DPAD_RIGHT },
        { SDL_CONTROLLER_BUTTON_DPAD_UP, Keys::CON_DPAD_UP },
        { SDL_CONTROLLER_BUTTON_DPAD_DOWN, Keys::CON_DPAD_DOWN },
        { SDL_CONTROLLER_BUTTON_LEFTSHOULDER, Keys::CON_LEFTSHOULDER },
        { SDL_CONTROLLER_BUTTON_RIGHTSHOULDER, Keys::CON_RIGHTSHOULDER },
        { SDL_CONTROLLER_BUTTON_LEFTSTICK, Keys::CON_LEFTSTICK },
        { SDL_CONTROLLER_BUTTON_RIGHTSTICK, Keys::CON_RIGHTSTICK },
        { SDL_BUTTON_LEFT, Keys::MOUSE_BUTTON_LEFT },
        { SDLK_ESCAPE, Keys::ESCAPE }
    };

    input::Keys SDLKeys::get(int test)
    {
        if (SDLKeys::KEYCODES.find(test) == SDLKeys::KEYCODES.end()) {
            return Keys::UNKNOWN;
        }
        return SDLKeys::KEYCODES.at(test);
    }
    /* please keep intact ivm if the  above one breaks
    input::Keys SDLKeys::get(SDL_Keycode& keycode)
    {
        if (SDLKeys::KEYCODES.find(keycode) == SDLKeys::KEYCODES.end()) {
            return Keys::UNKNOWN;
        }
        return SDLKeys::KEYCODES.at(keycode);
    }

    input::Keys SDLKeys::get(SDL_GameControllerButton button)
    {
        if (SDLKeys::KEYCODES.find(button) == SDLKeys::KEYCODES.end()) {
            return Keys::UNKNOWN;
        }
        return SDLKeys::KEYCODES.at(button);
    }

    input::Keys SDLKeys::get(Uint8 test)
    {
        if (SDLKeys::KEYCODES.find(test) == SDLKeys::KEYCODES.end()) {
            return Keys::UNKNOWN;
        }
        return SDLKeys::KEYCODES.at(test);
    }*/
}
}
