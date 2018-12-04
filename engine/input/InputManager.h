#pragma once

#include "engine/events/IEventHandler.h"
#include "engine/input/maps/InputMaps.h"
#include <engine/events/models/Subscription.h>
#include <memory>
#include <vector>

namespace engine {
namespace input {
    class InputManager {
    private:
        std::vector<std::weak_ptr<events::Subscription<maps::InputMap>>> m_subscriptions;
        maps::InputMaps m_inputMap{};
        events::IEventHandler* m_handler;

        void notifyObserver(const std::shared_ptr<events::Subscription<maps::InputMap>>& observer, int mapID);

    public:
        explicit InputManager(events::IEventHandler* handler)
            : m_handler{ handler } {};

        void handle(const std::unique_ptr<events::IEvent>& event_ptr);

        std::shared_ptr<events::Subscription<maps::InputMap>> subscribe(std::function<void(maps::InputMap, events::Subscription<maps::InputMap>&)> onNotify, int id);
        std::shared_ptr<events::Subscription<maps::InputMap>> subscribeAll(std::function<void(maps::InputMap, events::Subscription<maps::InputMap>&)> onNotify);

        void notifyAll();
        void update();
        maps::InputMaps& getMap();
        std::vector<int>& getConnectedControllers() const;
    };
}
}
