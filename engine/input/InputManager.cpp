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
            conMap.changed = true;
            if (con->m_isAnalog) {
                conMap.setValue(con->m_analogKey, con->m_axisValue);
            } else {
                conMap.setValue(con->m_key, (con->m_keyDown ? States::PRESSED : States::RELEASED));
            }
        } else if (auto mouse = dynamic_cast<events::MouseEvent*>(event_ptr.get())) {
            auto& KBM_Map = m_inputMap.getKBM();
            KBM_Map.changed = true;
            if (!mouse->m_isAnalog) {
                KBM_Map.setValue(mouse->m_key, (mouse->m_isPressed ? States::PRESSED : States::RELEASED));
            }
            KBM_Map.setValue(AnalogKeys::MOUSE_X, mouse->m_x);
            KBM_Map.setValue(AnalogKeys::MOUSE_Y, mouse->m_y);
        } else {
            auto& KBM_Map = m_inputMap.getKBM();
            KBM_Map.changed = true;
            if (auto down = dynamic_cast<events::KeyDownEvent*>(event_ptr.get())) {
                KBM_Map.setValue(down->value, States::PRESSED);
            } else if (auto up = dynamic_cast<events::KeyUpEvent*>(event_ptr.get())) {
                KBM_Map.setValue(up->value, States::RELEASED);
            }
        }
    }

    std::shared_ptr<events::Subscription<maps::InputMap>> InputManager::subscribe(
        std::function<void(maps::InputMap, events::Subscription<maps::InputMap>&)> onNotify, int id)
    {
        auto subscription = std::make_shared<events::Subscription<maps::InputMap>>(onNotify, id, false);
        m_subscriptions.push_back(subscription);
        std::cout << "subbed to controller: " << id << std::endl;
        return subscription;
    }

    std::shared_ptr<events::Subscription<maps::InputMap>> InputManager::subscribeAll(
        std::function<void(maps::InputMap, events::Subscription<maps::InputMap>&)> onNotify)
    {
        auto subscription = std::make_shared<events::Subscription<maps::InputMap>>(onNotify, -1, true);
        m_subscriptions.push_back(subscription);
        return subscription;
    }

    void InputManager::notifyAll()
    {
        for (const auto& weakObserver : m_subscriptions) {
            if (auto observer = weakObserver.lock()) {
                if (observer->subAll) {
                    for (size_t i = 0; i < m_handler->getConnectedControllers().size(); i++) {
                        notifyObserver(observer, (int)i);
                    }
                }
                notifyObserver(observer, observer->subbedTo);
            }
        }
    }

    void InputManager::notifyObserver(std::shared_ptr<events::Subscription<maps::InputMap>> observer, int mapID)
    {
        if (observer->isActive && m_inputMap.getMap(mapID).changed) {
            observer->update(m_inputMap.getMap(mapID), *observer);
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

    maps::InputMaps& InputManager::getMap()
    {
        return m_inputMap;
    }

    std::vector<int>& InputManager::getConnectedControllers() const
    {
        return m_handler->getConnectedControllers();
    }
}
}
