#include "SDLEventHandler.h"
#include <SDL.h>
#include <events/models/ControllerEvent.h>
#include <events/models/KeyDownEvent.h>
#include <events/models/KeyUpEvent.h>
#include <events/models/MouseEvent.h>
#include <events/models/QuitEvent.h>
#include <input/SDL_Input/SDL_ConKeys.h>
#include <input/SDL_Input/SDL_MouseKeys.h>

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
            return std::make_unique<MouseEvent>(event.button.x, event.button.y, input::sdl::SDL_MouseKeys::get(event.button.button), true);
        case SDL_MOUSEBUTTONUP:
            return std::make_unique<MouseEvent>(input::sdl::SDL_MouseKeys::get(event.button.button), false);
        case SDL_CONTROLLERAXISMOTION: {
            input::AnalogKeys key = input::sdl::SDL_Axis::get(event.caxis.axis);
            int value = std::abs(event.caxis.value) > deadZone ? event.caxis.value : 0;
            return std::make_unique<ControllerEvent>(event.cdevice.which, key, value);
        }
        case SDL_CONTROLLERBUTTONDOWN:
            return std::make_unique<ControllerEvent>(event.cdevice.which, input::sdl::SDL_ConKeys::get(event.cbutton.button), true);
        case SDL_CONTROLLERBUTTONUP:
            return std::make_unique<ControllerEvent>(event.cdevice.which, input::sdl::SDL_ConKeys::get(event.cbutton.button), false);
        case SDL_QUIT:
            return std::make_unique<QuitEvent>();
        case SDL_KEYUP:
            return std::make_unique<KeyUpEvent>(input::sdl::SDLKeys::get(event.key.keysym.sym));
        case SDL_KEYDOWN:
            if (event.key.repeat != 0u) {
                return nullptr; // ignore repeat events
            }
            return std::make_unique<KeyDownEvent>(input::sdl::SDLKeys::get(event.key.keysym.sym));
        case SDL_CONTROLLERDEVICEADDED: {
            SDL_GameControllerOpen(event.cdevice.which);
            connectedControllers.push_back((size_t)event.cdevice.which);
            return nullptr;
        }
        default:
            return nullptr;
        }
    }

    const std::vector<size_t>& SDLEventHandler::getConnectedControllers()
    {
        return connectedControllers;
    }
}
}
