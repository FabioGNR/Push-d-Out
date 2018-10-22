#include "EventManager.h"
#include <events/models/KeyUpEvent.h>
#include <events/models/KeyUpEvent.h>
#include <events/models/QuitEvent.h>
#include <input/InputManager.h>

namespace engine {
namespace events {
    bool EventManager::getEvents()
    {
        std::vector<std::shared_ptr<IEvent>> events = m_handler->getEvents();

        m_inputManager.update();
        for (const auto& event : events) {
            if (auto e = std::dynamic_pointer_cast<IControlEvent>(event)) {
                m_inputManager.handle(e);
            } else if (std::dynamic_pointer_cast<QuitEvent>(event)) { // TODO: eventually remove this
                return false;
            }
        }
        return true;
    }

    input::InputManager& EventManager::getInput()
    {
        return m_inputManager;
    }
}
}