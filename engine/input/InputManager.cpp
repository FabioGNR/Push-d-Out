#include <utility>

#include "InputManager.h"
#include <events/models/IControlEvent.h>
#include <events/models/KeyDownEvent.h>
#include <events/models/KeyUpEvent.h>
#include <map>
#include <utility>

namespace engine {
namespace input {
    void InputManager::handle(const std::shared_ptr<events::IControlEvent>& event)
    {
        if (auto down = std::dynamic_pointer_cast<events::KeyDownEvent>(event)) {
            m_keymap.setKeyState(down->value, KeyStates::PRESSED);
        } else if (auto up = std::dynamic_pointer_cast<events::KeyUpEvent>(event)) {
            m_keymap.setKeyState(up->value, KeyStates::RELEASED);
        }
    }

    std::shared_ptr<events::Subscription<KeyMap>> InputManager::subscribe(std::function<void(KeyMap, events::Subscription<KeyMap>&)> onNotify)
    {
        auto subscription = std::make_shared<events::Subscription<KeyMap>>(onNotify);
        m_subscriptions.push_back(subscription);
        return subscription;
    }

    void InputManager::notify()
    {
        for (const auto& observer : m_subscriptions) {
            if (observer->isActive) {
                observer->update(m_keymap, *observer);
            }
        }
    }

    void InputManager::update()
    {
        m_keymap.update();

        // remove inactive subscriptions
        auto it = m_subscriptions.begin();
        while (it != m_subscriptions.end()) {
            if (!(*it)->isActive) {
                it = m_subscriptions.erase(it);
            } else {
                ++it;
            }
        }
    }

    const KeyMap& InputManager::getKeyMap() const
    {
        return m_keymap;
    }
}
}
