#pragma once

#include "AnalogKeys.h"
#include <SDL2/SDL_gamecontroller.h>
#include <map>

namespace engine {
namespace input {
    struct SDL_Axis {
        static const std::map<SDL_GameControllerAxis, AnalogKeys> axises;
        static input::AnalogKeys get(SDL_GameControllerAxis axis);
    };
}
}