#pragma once

#include "IEventHandler.h"
#include <engine/input/InputManager.h>
#include <vector>

namespace engine {
namespace events {
    class EventManager {

    private:
        std::shared_ptr<IEventHandler> m_handler;
        input::InputManager m_inputManager;

    public:
        explicit EventManager(std::unique_ptr<IEventHandler> mapper)
            : m_handler { std::move(mapper) }
            , m_inputManager {m_handler} {};

        bool getEvents();
        input::InputManager& getInput();
    };
}
}
