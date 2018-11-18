#pragma once

#include "engine/events/IEventHandler.h"
#include "engine/input/maps/InputMap.h"
#include <engine/events/models/Subscription.h>
#include <memory>
#include <vector>

namespace engine {
namespace input {
    class InputManager {
    private:
        std::vector<std::weak_ptr<events::Subscription<maps::AnalogMap>>> m_subscriptions;
        maps::InputMap m_inputMap{};
        std::shared_ptr<events::IEventHandler> m_handler;

    public:
        explicit InputManager(std::shared_ptr<events::IEventHandler>& handler)
            : m_handler{ handler } {};

        void handle(const std::shared_ptr<events::IControlEvent>& event);

        std::shared_ptr<events::Subscription<maps::AnalogMap>> subscribe(std::function<void(maps::AnalogMap, events::Subscription<maps::AnalogMap>&)> onNotify, int id);
        std::shared_ptr<events::Subscription<maps::AnalogMap>> subscribe(std::function<void(maps::AnalogMap, events::Subscription<maps::AnalogMap>&)> onNotify);

        void notify();
        void update();
        maps::InputMap& getMap();
        size_t conAmount();
        bool openCon(int id);
    };
}
}
