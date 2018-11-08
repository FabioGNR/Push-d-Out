#include "InputManager.h"
#include <engine/events/models/ControllerEvent.h>
#include <engine/events/models/KeyDownEvent.h>
#include <engine/events/models/KeyUpEvent.h>

namespace engine {
namespace input {
    void InputManager::handle(const std::shared_ptr<events::IControlEvent>& event)
    {
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
        }
    }

    std::shared_ptr<events::Subscription<ControllerMap>> InputManager::subscribe(std::function<void(ControllerMap, events::Subscription<ControllerMap>&)> onNotify)
    {
        auto subscription = std::make_shared<events::Subscription<ControllerMap>>(onNotify);
        m_subscriptions.push_back(subscription);
        return subscription;
    }

    void InputManager::notify()
    {
        /*
    }
        for (const auto& observer : m_subscriptions) {
            if (observer.isActive) {
                observer->update(controlMap, *observer);
                */
        //if (!m_keymap.m_map.empty()) {
        for (const auto& weakObserver : m_subscriptions) {
            if (auto observer = weakObserver.lock()) {
                if (observer->isActive) {
                    observer->update(controlMap, *observer);
                }
            }
        }
        //}
    }

    void InputManager::update()
    {
        controlMap.update();

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
    /*
    const KeyMap& InputManager::getKeyMap() const
    {
        return m_keymap;
    }*/
}
}
