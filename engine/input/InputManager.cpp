#include <utility>

#include <map>
#include <utility>

#include "InputManager.h"
#include <events/models/IControlEvent.h>

namespace engine {
namespace input {
    void InputManager::storeInput(std::shared_ptr<events::IControlEvent> event)
    {
        m_keymap.setKey(std::move(event));
    }

    void InputManager::startInput()
    {
        m_keymap.m_map.clear();
    }

    std::shared_ptr<events::Subscription<Keymap>> InputManager::subscribe(std::function<void(Keymap)> onNotify)
    {
        auto subscription = std::make_shared<events::Subscription<Keymap>>(onNotify);
        m_subscriptions.push_back(subscription);
        return subscription;
    }

    void InputManager::notify()
    {
        if (m_keymap.m_map.empty()) {
            return;
        }

        for (const auto& observer : m_subscriptions) {
            if (observer->isActive) {
                observer->update(m_keymap);
            }
        }
    }
}
}
