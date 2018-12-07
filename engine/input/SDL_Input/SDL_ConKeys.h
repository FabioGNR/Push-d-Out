#pragma once

#include "engine/input/Keys.h"
#include <map>

namespace engine {
namespace input {
    namespace sdl {
        struct SDL_ConKeys {
            static const std::map<uint8_t, Keys> CON_KEYCODES;

            static Keys get(uint8_t SDL_Button);
        };
    }
}
}
