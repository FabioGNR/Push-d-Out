#pragma once

#include "IEventHandler.h"
#include "engine/input/AnalogKeys.h"
#include "engine/input/SDL_Axis.h"
#include <engine/input/SDLKeys.h>
#include <map>
#include <vector>

union SDL_Event;

namespace engine {
namespace events {
    class SDLEventHandler : public IEventHandler {
    private:
        const int deadZone = 15000;
        std::vector<int> connectedControllers;
        std::unique_ptr<IEvent> mapEvent(const SDL_Event& event);

    public:
        std::vector<std::unique_ptr<IEvent>> getEvents() override;
        size_t getConnectedControllers() override;
    };
}
}