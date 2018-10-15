#include "EventManager.h"
#include <events/models/QuitEvent.h>
#include <input/InputManager.h>

namespace engine {
namespace events {
    bool EventManager::getEvents()
    {
        SDLEventManager eventAdapter;
        std::vector<std::shared_ptr<IEvent>> events = eventAdapter.getEvents();

        m_inputManager.startInput();
        for (const auto& event : events) {
            if (auto e = std::dynamic_pointer_cast<IControlEvent>(event)) {
                m_inputManager.storeInput(e);
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