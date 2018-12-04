#include "SDL_ConKeys.h"
#include <SDL_gamecontroller.h>

namespace engine {
namespace input {
    namespace sdl {
        const std::map<uint8_t, Keys> SDL_ConKeys::CON_KEYCODES = {
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
        };

        Keys SDL_ConKeys::get(uint8_t SDL_Button)
        {
            if (SDL_ConKeys::CON_KEYCODES.find(SDL_Button) == SDL_ConKeys::CON_KEYCODES.end()) {
                return Keys::UNKNOWN;
            }
            return SDL_ConKeys::CON_KEYCODES.at(SDL_Button);
        }
    }
}
}