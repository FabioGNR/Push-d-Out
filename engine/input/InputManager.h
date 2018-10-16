#pragma once

#include "Keymap.h"
#include "events/models/Subscription.h"
#include <queue>
#include <vector>

namespace engine {
namespace input {
    class InputManager {
    private:
        std::vector<std::shared_ptr<events::Subscription<Keymap>>> m_subscriptions;
        Keymap m_keymap;

    public:
        void startInput();
        void storeInput(std::shared_ptr<events::IControlEvent> event);
        std::shared_ptr<events::Subscription<Keymap>> subscribe(std::function<void(Keymap)> onNotify);
        void notify();
    };
}
}
