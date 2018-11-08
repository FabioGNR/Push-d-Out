#include "InputManager.h"
#include <engine/events/models/ControllerEvent.h>
#include <engine/events/models/KeyDownEvent.h>
#include <engine/events/models/KeyUpEvent.h>

namespace engine {
namespace input {
    void InputManager::handle(const std::shared_ptr<events::IControlEvent>& event)
    {
        if (auto con = std::dynamic_pointer_cast<events::ControllerEvent>(event)) {

            auto conMap = m_inputMap.getMap(con->m_ID);
            if (con->m_axisValue == 0) {
                conMap.setValue(con->m_key, (con->m_keyDown ? KeyStates::PRESSED : KeyStates::RELEASED));
            } else {
                conMap.setValue(con->m_analogKey, con->m_axisValue);
            }
        } else {
            auto& KMB_Map = m_inputMap.getKBM();
            if (auto down = std::dynamic_pointer_cast<events::KeyDownEvent>(event)) {
                KMB_Map.setValue(down->value, KeyStates::PRESSED);
            } else if (auto up = std::dynamic_pointer_cast<events::KeyUpEvent>(event)) {
                KMB_Map.setValue(up->value, KeyStates::RELEASED);
            }
        }
        /*
        if (auto down = std::dynamic_pointer_cast<events::KeyDownEvent>(event)) {
            controlMap.setValue(down->value, KeyStates::PRESSED);
        } else if (auto up = std::dynamic_pointer_cast<events::KeyUpEvent>(event)) {
            controlMap.setValue(up->value, KeyStates::RELEASED);
        } else if (auto con = std::dynamic_pointer_cast<events::ControllerEvent>(event)) {
            if (conList.find(con->ID) == conList.end()) {
                conList.insert({ con->ID, std::make_shared<ControllerMap>() });
            } else {
                if (con->axisValue == 0) {
                    conList[con->ID]->setValue(con->value, (con->keyDown ? KeyStates::PRESSED : KeyStates::RELEASED));
                } else {
                    conList[con->ID]->setValue(con->value, con->axisValue);
                    //controlMap.setAxisValue(con->value, con->axisValue);
                }
            }
        }*/
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
}
}
