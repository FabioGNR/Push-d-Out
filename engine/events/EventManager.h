#pragma once

#include "SDLEventManager.h"
#include "input/InputManager.h"
#include <vector>

namespace engine {
namespace events {
    class EventManager {
    private:
        input::InputManager m_inputManager;

    public:
        EventManager() = default;

        bool getEvents();
        input::InputManager& getInput();
    };
}
}
