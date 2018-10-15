#pragma once

#include "input/SDLKeys.h"
#include <vector>

namespace engine {
namespace events {
    class SDLEventManager {
    private:
        std::shared_ptr<IEvent> mapEvent(SDL_Event event);
    public:
        std::vector<std::shared_ptr<IEvent>> getEvents();
    };
}
}