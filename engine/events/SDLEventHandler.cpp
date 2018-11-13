#include "SDLEventHandler.h"
#include <SDL.h>
#include <events/models/ControllerEvent.h>
#include <events/models/KeyDownEvent.h>
#include <events/models/KeyUpEvent.h>
#include <events/models/QuitEvent.h>

namespace engine {
namespace events {
    std::vector<std::shared_ptr<IEvent>> SDLEventHandler::getEvents()
    {
        std::vector<std::shared_ptr<IEvent>> events;
        SDL_Event event;

        while (SDL_PollEvent(&event) != 0) {
            events.push_back(mapEvent(event));
        }
        return events;
    }

    std::shared_ptr<IEvent> SDLEventHandler::mapEvent(SDL_Event& event)
    {
        switch (event.type) {
        case SDL_QUIT:
            return std::make_shared<QuitEvent>();
        case SDL_KEYUP:
            return std::make_shared<KeyUpEvent>(input::SDLKeys::get(event.key.keysym.sym));
        case SDL_KEYDOWN:
            if (event.key.repeat != 0u) {
                return nullptr; // ignore repeat events
            }
            return std::make_shared<KeyDownEvent>(input::SDLKeys::get(event.key.keysym.sym));
        case SDL_CONTROLLERDEVICEADDED: {
            SDL_GameControllerOpen(conCount++);
            return nullptr;
        }
        case SDL_CONTROLLERBUTTONDOWN:
            return std::make_shared<ControllerEvent>(event.cdevice.which, input::SDLKeys::get((SDL_GameControllerButton)event.cbutton.button), true);
        case SDL_CONTROLLERBUTTONUP:
            return std::make_shared<ControllerEvent>(event.cdevice.which, input::SDLKeys::get((SDL_GameControllerButton)event.cbutton.button), false);
        case SDL_CONTROLLERAXISMOTION: {
            input::AnalogKeys key = input::SDL_Axis::get((SDL_GameControllerAxis)event.caxis.axis);
            /*
            if (event.caxis.axis == SDL_CONTROLLER_AXIS_LEFTX) {
                key = input::AnalogKeys::CON_LEFTSTICK_X;
            } else if (event.caxis.axis == SDL_CONTROLLER_AXIS_LEFTY) {
                key = input::AnalogKeys::CON_LEFTSTICK_Y;
            } else if (event.caxis.axis == SDL_CONTROLLER_AXIS_RIGHTX) {
                key = input::AnalogKeys::CON_RIGHTSTICK_X;
            } else if (event.caxis.axis == SDL_CONTROLLER_AXIS_RIGHTY) {
                key = input::AnalogKeys::CON_RIGHTSTICK_Y;
            } else if (event.caxis.axis == SDL_CONTROLLER_AXIS_TRIGGERLEFT) {
                key = input::AnalogKeys::CON_TRIGGER_LEFT;
            } else if (event.caxis.axis == SDL_CONTROLLER_AXIS_TRIGGERRIGHT) {
                key = input::AnalogKeys::CON_TRIGGER_RIGHT;
            } else {
                return nullptr;
            }*/
            int value = 0;
            if (event.caxis.value > 15000 || event.caxis.value < -15000) {
                value = event.caxis.value;
            }

            return std::make_shared<ControllerEvent>(event.cdevice.which, key, value);
        }
            /*
        case SDL_JOYDEVICEADDED:
            std::cout << "Joystick added: " << event.cdevice.which << std::endl;
            //SDL_JoystickOpen(conCount++);
            return nullptr;
        case SDL_JOYBUTTONDOWN:
            std::cout << "Controller button down" << std::endl;
            return std::make_shared<ControllerEvent>(input::Keys::CON_START, true, event.cdevice.which);
        case SDL_JOYAXISMOTION: {
            input::AnalogKeys key;
            int axis = (int)event.jaxis.axis;
            std::cout << (int)event.jaxis.axis << std::endl;
            if (axis < 3) {
                std::cout << "L" << std::endl;
            } else if (axis > 5) {
                std::cout << "B" << std::endl;
            } else {
                std::cout << "R" << std::endl;
            }

            if (event.jaxis.axis == 0) {
                key = input::AnalogKeys::CON_LEFTSTICK_X;
            } else if (event.jaxis.axis == 1) {
                key = input::AnalogKeys::CON_LEFTSTICK_Y;
            } else if (event.jaxis.axis == 2) {
                key = input::AnalogKeys::CON_LEFTSTICK_Z;
            } else if (event.jaxis.axis == 3) {
                key = input::AnalogKeys::CON_RIGHTSTICK_X;
            } else if (event.jaxis.axis == 4) {
                key = input::AnalogKeys::CON_RIGHTSTICK_Y;
            } else if (event.jaxis.axis == 5) {
                key = input::AnalogKeys::CON_RIGHTSTICK_Z;
            } else if (event.jaxis.axis == 6) {
                key = input::AnalogKeys::CON_TRIGGER_LEFT;
            } else if (event.jaxis.axis == 7) {
                key = input::AnalogKeys::CON_TRIGGER_RIGHT;
            } else {
                return nullptr;
            }

            //std::pair<int , int> test = std::make_pair(1, 2); TODO check this
            //std::cout << "Controller joy axis motion" << std::endl;
            return std::make_shared<ControllerEvent>(key, event.jaxis.value, event.cdevice.which);
        }*/
        default:
            return nullptr;
        }
    }
}
}
