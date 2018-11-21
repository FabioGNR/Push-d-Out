#pragma once

#include "AnalogKeys.h"
#include <map>

namespace engine {
namespace input {
    struct SDL_Axis {
        static const std::map<uint8_t, AnalogKeys> axises;
        static input::AnalogKeys get(uint8_t axis);
    };
}
}