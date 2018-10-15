#include "SDLEventAdapter.h"
#include <events/models/QuitEvent.h>
#include <events/models/UnknownEvent.h>

namespace engine {
namespace events {
    std::vector<IEvent*> SDLEventAdapter::getEvents()
    {
        std::vector<IEvent*> events;
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            events.push_back(sortEvents(event));
        }
        return events;
    }

    IEvent* SDLEventAdapter::sortEvents(SDL_Event event)
    {
        switch (event.type) {
        case SDL_QUIT:
            return new QuitEvent();
        case SDL_KEYUP:
            return km.getKeyValue(event, false);
        case SDL_KEYDOWN:
            return km.getKeyValue(event, true);
        default:
            return new UnknownEvent();
        }
    }
}
}
