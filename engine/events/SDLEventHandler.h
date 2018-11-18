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
        std::map<int, bool> cCon;
        std::shared_ptr<IEvent> mapEvent(SDL_Event& event);

    public:
        std::vector<std::shared_ptr<IEvent>> getEvents() override;
        bool openCon(int id) override;
        size_t getcCon() override;
    };
}
}