#include "SDLEventHandler.h"

#include <SDL.h>

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
        default:
            return nullptr;
        }
    }
}
}
