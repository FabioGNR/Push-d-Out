#include "SDLEventManager.h"
#include <events/models/KeyEvent.h>
#include <events/models/QuitEvent.h>

namespace engine {
namespace events {
    std::vector<std::shared_ptr<IEvent>> SDLEventManager::getEvents()
    {
        std::vector<std::shared_ptr<IEvent>> events;
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            events.push_back(mapEvent(event));
        }
        return events;
    }

    std::shared_ptr<IEvent> SDLEventManager::mapEvent(SDL_Event event)
    {
        switch (event.type) {
        case SDL_QUIT:
            return std::make_shared<QuitEvent>();
        case SDL_KEYUP:
            return std::make_shared<KeyEvent>(input::SDLKeys::get(event.key.keysym.sym), false);
        case SDL_KEYDOWN:
            return std::make_shared<KeyEvent>(input::SDLKeys::get(event.key.keysym.sym), true);
        default:
            return nullptr;
        }
    }
}
}
