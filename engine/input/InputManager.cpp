#include "InputManager.h"
#include <events/models/IControlEvent.h>

namespace engine {
namespace input {
    void InputManager::storeInput(std::shared_ptr<events::IControlEvent> event)
    {
        m_keymap->insert(std::pair<Keys, std::shared_ptr<events::IControlEvent>>(event->getValue(), event));
    }

    void InputManager::startInput()
    {
        m_keymap->clear();
    }

    void InputManager::subscribe(IObserver* observer)
    {
        observers.push_back(observer);
    }

    void InputManager::notify()
    {
        if (m_keymap->empty()) {
            return;
        }
        for (auto& observer : observers) {
            observer->onInputUpdate(*m_keymap);
        }
    }
}
}
