#include "SDLEventHandler.h"
#include <SDL.h>
#include <events/models/ControllerEvent.h>
#include <events/models/KeyDownEvent.h>
#include <events/models/KeyUpEvent.h>
#include <events/models/MouseEvent.h>
#include <events/models/QuitEvent.h>

namespace engine {
namespace events {
    std::vector<std::unique_ptr<IEvent>> SDLEventHandler::getEvents()
    {
        std::vector<std::unique_ptr<IEvent>> events;
        SDL_Event event;

        while (SDL_PollEvent(&event) != 0) {
            events.push_back(mapEvent(event));
        }
        return events;
    }

    std::unique_ptr<IEvent> SDLEventHandler::mapEvent(const SDL_Event& event)
    {
        switch (event.type) {
        case SDL_MOUSEMOTION:
            return std::make_unique<MouseEvent>(event.motion.x, event.motion.y);
        case SDL_MOUSEBUTTONDOWN:
            return std::make_unique<MouseEvent>(event.button.x, event.button.y, input::SDLKeys::get(input::SDLKeys::mouseStart + event.button.button), true);
        case SDL_MOUSEBUTTONUP:
            return std::make_unique<MouseEvent>(input::SDLKeys::get(input::SDLKeys::mouseStart + event.button.button), false);
        case SDL_CONTROLLERAXISMOTION: {
            input::AnalogKeys key = input::SDL_Axis::get(event.caxis.axis);
            int value = event.caxis.value > deadZone || event.caxis.value < -deadZone ? event.caxis.value : 0;
            return std::make_unique<ControllerEvent>(event.cdevice.which, key, value);
        }
        case SDL_CONTROLLERBUTTONDOWN:
            return std::make_unique<ControllerEvent>(event.cdevice.which, input::SDLKeys::get((SDL_GameControllerButton)event.cbutton.button), true);
        case SDL_CONTROLLERBUTTONUP:
            return std::make_unique<ControllerEvent>(event.cdevice.which, input::SDLKeys::get((SDL_GameControllerButton)event.cbutton.button), false);
        case SDL_QUIT:
            return std::make_unique<QuitEvent>();
        case SDL_KEYUP:
            return std::make_unique<KeyUpEvent>(input::SDLKeys::get(event.key.keysym.sym));
        case SDL_KEYDOWN:
            if (event.key.repeat != 0u) {
                return nullptr; // ignore repeat events
            }
            return std::make_unique<KeyDownEvent>(input::SDLKeys::get(event.key.keysym.sym));
        case SDL_CONTROLLERDEVICEADDED: {
            SDL_GameControllerOpen(event.cdevice.which);
            connectedControllers.push_back(event.cdevice.which);
            return nullptr;
        }
        default:
            return nullptr;
        }
    }

    size_t SDLEventHandler::getConnectedControllers()
    {
        return connectedControllers.size();
    }
}
}
