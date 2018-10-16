#pragma once

#include "KeyMap.h"
#include "events/models/Subscription.h"
#include <events/models/KeyUpEvent.h>
#include <queue>
#include <vector>

namespace engine {
namespace input {
    class InputManager {
    private:
        std::vector<std::shared_ptr<events::Subscription<KeyMap>>> m_subscriptions;
        KeyMap m_keymap;

    public:
        void handle(const std::shared_ptr<events::IControlEvent> &event);
        std::shared_ptr<events::Subscription<KeyMap>> subscribe(std::function<void(KeyMap)> onNotify);
        void notify();
        void update();
    };
}
}
