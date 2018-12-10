#include "SDL_MouseKeys.h"
#include <SDL_mouse.h>

namespace engine {
namespace input {
    namespace sdl {
        const std::map<uint8_t, Keys> SDL_MouseKeys::MOUSE_KEYCODES = {
            { SDL_BUTTON_LEFT, Keys::MOUSE_BUTTON_LEFT },
            { SDL_BUTTON_RIGHT, Keys::MOUSE_BUTTON_RIGHT }
        };

        Keys SDL_MouseKeys::get(const uint8_t SDL_Button)
        {
            if (SDL_MouseKeys::MOUSE_KEYCODES.find(SDL_Button) == SDL_MouseKeys::MOUSE_KEYCODES.end()) {
                return Keys::UNKNOWN;
            }
            return SDL_MouseKeys::MOUSE_KEYCODES.at(SDL_Button);
        }
    }
}
}