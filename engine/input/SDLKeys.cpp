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
        { SDLK_ESCAPE, Keys::ESCAPE },
        { SDLK_F1, Keys::F1 },
        { SDLK_F2, Keys::F2 },
        { SDLK_F3, Keys::F3 },
        { SDLK_F4, Keys::F4 },
        { SDLK_F5, Keys::F5 },
        { SDLK_F6, Keys::F6 },
        { SDLK_F7, Keys::F7 },
        { SDLK_F8, Keys::F8 },
        { SDLK_F9, Keys::F9 },
        { SDLK_F10, Keys::F10 },
        { SDLK_F11, Keys::F11 },
        { SDLK_F12, Keys::F12 },
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
        { SDL_CONTROLLER_BUTTON_START, Keys::CON_START },
        { mouseStart + 1, Keys::MOUSE_BUTTON_LEFT }
    };

    input::Keys SDLKeys::get(const int SDL_Key)
    {
        if (SDLKeys::KEYCODES.find(SDL_Key) == SDLKeys::KEYCODES.end()) {
            return Keys::UNKNOWN;
        }
        return SDLKeys::KEYCODES.at(SDL_Key);
    }
}
}
