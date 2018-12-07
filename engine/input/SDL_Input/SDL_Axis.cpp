#include "SDL_Axis.h"
#include <SDL2/SDL_gamecontroller.h>

namespace engine {
namespace input {
    namespace sdl {
        // because SDL_GameControllerAxis is an enum, it cannot be forward declared
        // to work around this the enum values are converted to uint8_t
        const std::map<uint8_t, AnalogKeys> SDL_Axis::axises = {
            { static_cast<uint8_t>(SDL_CONTROLLER_AXIS_LEFTX), input::AnalogKeys::CON_LEFTSTICK_X },
            { static_cast<uint8_t>(SDL_CONTROLLER_AXIS_LEFTY), input::AnalogKeys::CON_LEFTSTICK_Y },
            { static_cast<uint8_t>(SDL_CONTROLLER_AXIS_RIGHTX), input::AnalogKeys::CON_RIGHTSTICK_X },
            { static_cast<uint8_t>(SDL_CONTROLLER_AXIS_RIGHTY), input::AnalogKeys::CON_RIGHTSTICK_Y },
            { static_cast<uint8_t>(SDL_CONTROLLER_AXIS_TRIGGERLEFT), input::AnalogKeys::CON_TRIGGER_LEFT },
            { static_cast<uint8_t>(SDL_CONTROLLER_AXIS_TRIGGERRIGHT), input::AnalogKeys::CON_TRIGGER_RIGHT }
        };

        input::AnalogKeys SDL_Axis::get(const uint8_t axis)
        {
            if (SDL_Axis::axises.find(axis) == SDL_Axis::axises.end()) {
                return AnalogKeys::CON_UNKNOWN;
            }
            return SDL_Axis::axises.at(axis);
        }
    }
}
}