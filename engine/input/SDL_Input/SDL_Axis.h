#pragma once

#include "engine/input/AnalogKeys.h"
#include <map>

namespace engine {
namespace input {
    namespace sdl {
        struct SDL_Axis {
            static const std::map<uint8_t, AnalogKeys> axises;
            static input::AnalogKeys get(uint8_t axis);
        };
    }
}
}