#pragma once

#include "input/SDLKeyMap.h"
#include <vector>

namespace engine {
namespace events {
    class SDLEventAdapter {
    private:
        IEvent* sortEvents(SDL_Event event);

        input::SDLKeyMap km;

    public:
        std::vector<IEvent*> getEvents();
    };
}
}