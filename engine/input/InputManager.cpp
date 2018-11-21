#include "InputManager.h"
#include <engine/events/models/ControllerEvent.h>
#include <engine/events/models/KeyDownEvent.h>
#include <engine/events/models/KeyUpEvent.h>
#include <events/models/MouseEvent.h>

namespace engine {
namespace input {
    void InputManager::handle(const std::unique_ptr<events::IEvent>& event_ptr)
    {
        if (auto con = dynamic_cast<events::ControllerEvent*>(event_ptr.get())) {
            auto& conMap = m_inputMap.getMap(con->m_ID);
            if (con->m_isAnalog) {
                conMap.setValue(con->m_analogKey, con->m_axisValue);
            } else {
                conMap.setValue(con->m_key, (con->m_keyDown ? KeyStates::PRESSED : KeyStates::RELEASED));
            }
        } else if (auto mouse = dynamic_cast<events::MouseEvent*>(event_ptr.get())) {
            auto& KBM_Map = m_inputMap.getKBM();
            if (mouse->m_isAnalog) {
                KBM_Map.setValue(AnalogKeys::MOUSE_X, mouse->m_x);
                KBM_Map.setValue(AnalogKeys::MOUSE_Y, mouse->m_y);
            } else {
                KBM_Map.setValue(mouse->m_key, (mouse->m_isPressed ? KeyStates::PRESSED : KeyStates::RELEASED));
            }
        } else {
            auto& KMB_Map = m_inputMap.getKBM();
            if (auto down = dynamic_cast<events::KeyDownEvent*>(event_ptr.get())) {
                KMB_Map.setValue(down->value, KeyStates::PRESSED);
            } else if (auto up = dynamic_cast<events::KeyUpEvent*>(event_ptr.get())) {
                KMB_Map.setValue(up->value, KeyStates::RELEASED);
            }
        }
    }

    std::shared_ptr<events::Subscription<maps::AnalogMap>> InputManager::subscribe(
        std::function<void(maps::AnalogMap, events::Subscription<maps::AnalogMap>&)> onNotify, int id)
    {
        auto subscription = std::make_shared<events::Subscription<maps::AnalogMap>>(onNotify, id);
        m_subscriptions.push_back(subscription);
        return subscription;
    }

    std::shared_ptr<events::Subscription<maps::AnalogMap>> InputManager::subscribe(
        std::function<void(maps::AnalogMap, events::Subscription<maps::AnalogMap>&)> onNotify)
    {
        auto subscription = std::make_shared<events::Subscription<maps::AnalogMap>>(onNotify, -1);
        m_subscriptions.push_back(subscription);
        return subscription;
    }

    void InputManager::notify()
    {
        for (const auto& weakObserver : m_subscriptions) {
            if (auto observer = weakObserver.lock()) {
                if (observer->isActive) {
                    observer->update(m_inputMap.getMap(observer->subbedTo), *observer);
                }
            }
        }
    }

    void InputManager::update()
    {
        m_inputMap.update();

        // remove inactive subscriptions
        auto it = m_subscriptions.begin();
        while (it != m_subscriptions.end()) {
            if (auto observer = (*it).lock()) {
                if (observer->isActive) {
                    ++it; // move to the next observer
                    continue; // observer is still active so no need to remove it
                }
            }
            // if the observer failed to lock or is no longer active
            // remove the subscription as it's no longer valid
            it = m_subscriptions.erase(it);
        }
    }
    maps::InputMap& InputManager::getMap()
    {
        return m_inputMap;
    }

    size_t InputManager::connectedControllerAmount()
    {
        return m_handler->getConnectedControllers();
    }

    bool InputManager::openController(int id)
    {
        return m_handler->openController(id);
    }
}
}
