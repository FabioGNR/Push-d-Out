#pragma once

#include <map>
#include <SDL2/SDL_gamecontroller.h>
#include "AnalogKeys.h"

namespace engine{
    namespace input{
        struct SDL_Axis{
            static const std::map<SDL_GameControllerAxis, AnalogKeys> axises;
            static input::AnalogKeys get(SDL_GameControllerAxis axis);
        };
    }
}