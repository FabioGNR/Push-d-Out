#include "InputManager.h"
#include <engine/events/models/ControllerEvent.h>
#include <engine/events/models/KeyDownEvent.h>
#include <engine/events/models/KeyUpEvent.h>
#include <events/models/MouseEvent.h>

namespace engine {
namespace input {
    void InputManager::handle(const std::shared_ptr<events::IControlEvent>& event)
    {
        if (auto con = std::dynamic_pointer_cast<events::ControllerEvent>(event)) {
            auto& conMap = m_inputMap.getMap(con->m_ID);
            if (con->m_isAnalog) {
                conMap.setValue(con->m_analogKey, con->m_axisValue);
            } else {
                conMap.setValue(con->m_key, (con->m_keyDown ? KeyStates::PRESSED : KeyStates::RELEASED));
            }
        } else if (auto mouse = std::dynamic_pointer_cast<events::MouseEvent>(event)) {
            auto& KBM_Map = m_inputMap.getKBM();
            if (mouse->m_isAnalog) {
                KBM_Map.setValue(AnalogKeys::MOUSE_X, mouse->m_x);
                KBM_Map.setValue(AnalogKeys::MOUSE_Y, mouse->m_y);
            } else {
                KBM_Map.setValue(mouse->m_key, (mouse->m_isPressed ? KeyStates::PRESSED : KeyStates::RELEASED));
            }
        } else {
            auto& KMB_Map = m_inputMap.getKBM();
            if (auto down = std::dynamic_pointer_cast<events::KeyDownEvent>(event)) {
                KMB_Map.setValue(down->value, KeyStates::PRESSED);
            } else if (auto up = std::dynamic_pointer_cast<events::KeyUpEvent>(event)) {
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

    int InputManager::conAmount()
    {
        return m_handler->getcCon();
    }

    bool InputManager::openCon(int id)
    {
        return m_handler->openCon(id);
    }
}
}
