#include "SDLEventHandler.h"
#include <events/models/ControllerEvent.h>
#include <events/models/KeyDownEvent.h>
#include <events/models/KeyUpEvent.h>
#include <events/models/QuitEvent.h>

//#include "input/Keys.h" // TODO remove

namespace engine {
namespace events {
    std::vector<std::shared_ptr<IEvent>> SDLEventHandler::getEvents()
    {
        std::vector<std::shared_ptr<IEvent>> events;
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            events.push_back(mapEvent(event));
        }
        return events;
    }

    std::shared_ptr<IEvent> SDLEventHandler::mapEvent(SDL_Event event)
    {
        switch (event.type) {
        case SDL_QUIT:
            return std::make_shared<QuitEvent>();
        case SDL_KEYUP:
            return std::make_shared<KeyUpEvent>(input::SDLKeys::get(event.key.keysym.sym));
        case SDL_KEYDOWN:
            return std::make_shared<KeyDownEvent>(input::SDLKeys::get(event.key.keysym.sym));
            /*
        case SDL_CONTROLLERDEVICEADDED:
            SDL_GameControllerOpen(conCount++);
            return std::make_shared<ControllerEvent>(input::Keys::CON_GUIDE, conCount);
        case SDL_CONTROLLERBUTTONDOWN:
            return std::make_shared<ControllerEvent>(input::SDLKeys::get(event.cbutton.button), conCount);*/
        case SDL_JOYDEVICEADDED:
            std::cout << "Controller added: " << event.cdevice.which << std::endl;
            SDL_JoystickOpen(conCount++);
            return std::make_shared<ControllerEvent>(input::Keys::CON_START, false, event.cdevice.which);
        case SDL_JOYBUTTONDOWN:
            std::cout << "Controller button down" << std::endl;
            return std::make_shared<ControllerEvent>(input::Keys::CON_START, true, event.cdevice.which);
        case SDL_JOYAXISMOTION: {
            input::Keys key;
            int axis = (int)event.jaxis.axis;
            //std::cout << (int)event.jaxis.axis << std::endl;
            if (axis < 3) {
                std::cout << "L" << std::endl;
            } else if (axis > 5) {
                std::cout << "B" << std::endl;
            } else {
                std::cout << "R" << std::endl;
            }

            if (event.jaxis.axis == 0) {
                key = input::Keys::CON_LEFTSTICK_X;
            } else if (event.jaxis.axis == 1) {
                key = input::Keys::CON_LEFTSTICK_Y;
            } else if (event.jaxis.axis == 2) {
                key = input::Keys::CON_LEFTSTICK_Z;
            } else if (event.jaxis.axis == 3) {
                key = input::Keys::CON_RIGHTSTICK_X;
            } else if (event.jaxis.axis == 4) {
                key = input::Keys::CON_RIGHTSTICK_Y;
            } else if (event.jaxis.axis == 5) {
                key = input::Keys::CON_RIGHTSTICK_Z;
            } else if (event.jaxis.axis == 6) {
                key = input::Keys::CON_LEFTSHOULDER;
            } else if (event.jaxis.axis == 7) {
                key = input::Keys::CON_RIGHTSHOULDER;
            } else {
                key = input::Keys::CON_START;
            }

            //std::pair<int , int> test = std::make_pair(1, 2); TODO check this
            std::cout << "Controller joy axis motion" << std::endl;
            return std::make_shared<ControllerEvent>(key, event.jaxis.value, conCount);
        }
        default:
            return nullptr;
        }
    }
}
}
