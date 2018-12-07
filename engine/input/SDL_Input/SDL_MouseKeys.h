#pragma once

#include "engine/input/Keys.h"
#include <map>

namespace engine {
namespace input {
    namespace sdl {
        struct SDL_MouseKeys {
            static const std::map<uint8_t, Keys> MOUSE_KEYCODES;

            static Keys get(uint8_t SDL_Button);
        };
    }
}
}
