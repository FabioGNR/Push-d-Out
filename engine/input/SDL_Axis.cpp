#include "SDL_Axis.h"

namespace engine {
namespace input {
    const std::map<SDL_GameControllerAxis, AnalogKeys> SDL_Axis::axises = {
        { SDL_CONTROLLER_AXIS_LEFTX, input::AnalogKeys::CON_LEFTSTICK_X },
        { SDL_CONTROLLER_AXIS_LEFTY, input::AnalogKeys::CON_LEFTSTICK_Y },
        { SDL_CONTROLLER_AXIS_RIGHTX, input::AnalogKeys::CON_RIGHTSTICK_X },
        { SDL_CONTROLLER_AXIS_RIGHTY, input::AnalogKeys::CON_RIGHTSTICK_Y },
        { SDL_CONTROLLER_AXIS_TRIGGERLEFT, input::AnalogKeys::CON_TRIGGER_LEFT },
        { SDL_CONTROLLER_AXIS_TRIGGERRIGHT, input::AnalogKeys::CON_TRIGGER_RIGHT }
    };

    input::AnalogKeys SDL_Axis::get(SDL_GameControllerAxis axis)
    {
        if (SDL_Axis::axises.find(axis) == SDL_Axis::axises.end()) {
            return CON_UNKNOWN;
        }
        return SDL_Axis::axises.at(axis);
    }
}
}