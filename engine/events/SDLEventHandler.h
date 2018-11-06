#pragma once

#include "IEventHandler.h"
#include "input/SDLKeys.h"
#include <vector>

namespace engine {
namespace events {
    class SDLEventHandler : public IEventHandler {
    private:
        std::shared_ptr<IEvent> mapEvent(SDL_Event event);
        int conCount = 0;

    public:
        std::vector<std::shared_ptr<IEvent>> getEvents() override;
    };
}
}