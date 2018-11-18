#include "SDLEventHandler.h"
#include <SDL.h>
#include <events/models/ControllerEvent.h>
#include <events/models/KeyDownEvent.h>
#include <events/models/KeyUpEvent.h>
#include <events/models/MouseEvent.h>
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
        case SDL_MOUSEMOTION:
            return std::make_shared<MouseEvent>(event.motion.x, event.motion.y);
        case SDL_MOUSEBUTTONDOWN:
            return std::make_shared<MouseEvent>(input::SDLKeys::get(event.button.button), true);
        case SDL_CONTROLLERAXISMOTION: {
            input::AnalogKeys key = input::SDL_Axis::get((SDL_GameControllerAxis)event.caxis.axis);
            int value = event.caxis.value > deadZone || event.caxis.value < -deadZone ? event.caxis.value : 0;
            /*if (event.caxis.value > deadZone || event.caxis.value < -deadZone) {
                    value = event.caxis.value;
                }*/

            return std::make_shared<ControllerEvent>(event.cdevice.which, key, value);
        }
        case SDL_CONTROLLERBUTTONDOWN:
            return std::make_shared<ControllerEvent>(event.cdevice.which, input::SDLKeys::get((SDL_GameControllerButton)event.cbutton.button), true);
        case SDL_CONTROLLERBUTTONUP:
            return std::make_shared<ControllerEvent>(event.cdevice.which, input::SDLKeys::get((SDL_GameControllerButton)event.cbutton.button), false);

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
            cCon.insert({ event.cbutton.which, false });
            std::cout << "C-CON: " << event.cbutton.which << std::endl;
            return nullptr;
        }
        default:
            return nullptr;
        }
    }

    bool SDLEventHandler::openCon(int id)
    {
        if (id < 0 || cCon.find(id) == cCon.end()) {
            return false;
        } else {
            SDL_GameControllerOpen(id);
            cCon[id] = true;
            std::cout << "C-OPN: " << id << std::endl;
            return true;
        }
    }

    size_t SDLEventHandler::getcCon()
    {
        return cCon.size();
    }
}
}
