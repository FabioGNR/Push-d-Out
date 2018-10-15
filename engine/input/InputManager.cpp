#include "InputManager.h"
#include <events/models/IControlEvent.h>

namespace engine {
namespace input {
    void InputManager::storeInput(events::IControlEvent* event)
    {
        keyMap->insert(std::pair<Keys, events::IControlEvent*>(event->getValue(), event));
    }

    void InputManager::startInput()
    {
        keyMap->clear();
    }

    void InputManager::subscribe(IObserver* observer)
    {
        observers.push_back(observer);
    }

    void InputManager::notify()
    {
        if (keyMap->empty()) {
            return;
        }
        for (auto& observer : observers) {
            observer->update(*keyMap);
        }
    }
}
}
