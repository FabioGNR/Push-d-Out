#include "InputManager.h"


namespace engine {
namespace input {
    void InputManager::handle(const std::shared_ptr<events::IControlEvent>& event)
    {
        if (auto down = std::dynamic_pointer_cast<events::KeyDownEvent>(event)) {
            controlMap.setKeyState(down->value, KeyStates::PRESSED);
        } else if (auto up = std::dynamic_pointer_cast<events::KeyUpEvent>(event)) {
            controlMap.setKeyState(up->value, KeyStates::RELEASED);
        } else if (auto con = std::dynamic_pointer_cast<events::ControllerEvent>(event)) {
            if (conList.find(con->ID) == conList.end()) {
                conList.insert({ con->ID, std::make_shared<models::ControllerMap>() });
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

    std::shared_ptr<events::Subscription<ControlMap>> InputManager::subscribe(std::function<void(ControlMap, events::Subscription<ControlMap>&)> onNotify)
    {
        auto subscription = std::make_shared<events::Subscription<ControlMap>>(onNotify);
        m_subscriptions.push_back(subscription);
        return subscription;
    }

    void InputManager::notify()
    {
        for (const auto& observer : m_subscriptions) {
            if (observer->isActive) {
                observer->update(controlMap, *observer);
            }
        }
    }

    void InputManager::update()
    {
        controlMap.update();

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
}
}
