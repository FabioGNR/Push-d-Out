#pragma once

#include "IEventHandler.h"
#include "input/InputManager.h"
#include <vector>

namespace engine {
namespace events {
    class EventManager {

    private:
        input::InputManager m_inputManager;
        std::unique_ptr<IEventHandler> m_handler;

    public:
        EventManager(std::unique_ptr<IEventHandler> mapper)
            : m_handler{ std::move(mapper) } {};

        bool getEvents();
        input::InputManager& getInput();
    };
}
}
