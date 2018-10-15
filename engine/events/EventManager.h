#pragma once

#include "SDLEventAdapter.h"
#include "input/InputManager.h"
#include <vector>

namespace engine {
namespace events {
    class EventManager {
    private:
        input::InputManager im;

    public:
        bool getEvents();

        input::InputManager* getInput();
    };
}
}
