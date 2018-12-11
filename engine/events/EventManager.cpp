#include "EventManager.h"
#include <events/models/KeyUpEvent.h>
#include <events/models/QuitEvent.h>
#include <input/InputManager.h>

namespace engine {
namespace events {
    bool EventManager::getEvents()
    {
        std::vector<std::unique_ptr<IEvent>> events = m_handler->getEvents();

        m_inputManager.update();
        for (const auto& event : events) {
            if (dynamic_cast<IControlEvent*>(event.get()) != nullptr) {
                m_inputManager.handle(std::move(event));
            } else if (dynamic_cast<QuitEvent*>(event.get()) != nullptr) { // TODO: eventually remove this
                return false;
            }
        }
        return true;
    }

    input::InputManager* EventManager::getInput()
    {
        return &m_inputManager;
    }
}
}