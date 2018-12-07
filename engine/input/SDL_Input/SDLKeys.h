#pragma once

#include "engine/input/Keys.h"
#include <map>

using SDL_Keycode = int;

namespace engine {
namespace input {
    namespace sdl {
        struct SDLKeys {
            static const int mouseStart = 813;
            static const std::map<SDL_Keycode, Keys> KEYCODES;

            static Keys get(int SDL_Key);
        };
    }
}
}