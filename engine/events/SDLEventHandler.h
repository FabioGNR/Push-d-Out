#pragma once

#include "IEventHandler.h"
#include "engine/input/AnalogKeys.h"
#include "engine/input/SDL_Input/SDL_Axis.h"
#include <engine/input/SDL_Input/SDLKeys.h>
#include <map>
#include <vector>

union SDL_Event;

namespace engine {
namespace events {
    class SDLEventHandler : public IEventHandler {
    private:
        const int deadZone = 2000;
        const double controllerAxisMax = 32768.0;
        std::vector<size_t> connectedControllers;
        std::unique_ptr<IEvent> mapEvent(const SDL_Event& event);

    public:
        std::vector<std::unique_ptr<IEvent>> getEvents() override;
        const std::vector<size_t>& getConnectedControllers() override;
    };
}
}