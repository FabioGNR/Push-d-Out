#pragma once

#include "Maps/ControllerMap.h"
#include "events/models/Subscription.h"
#include "input/Maps/KeyMap.h"
#include <events/models/KeyUpEvent.h>
#include <input/Maps/ControlMap.h>
#include <input/Maps/OtherMap.h>
#include <map>
#include <memory>
#include <queue>
#include <vector>

namespace engine {
namespace input {
    class InputManager {
    private:
        std::vector<std::shared_ptr<events::Subscription<ControlMap>>> m_subscriptions;
        ControlMap controlMap;
        std::map<int, std::shared_ptr<models::ControllerMap>> conList;

    public:
        void handle(const std::shared_ptr<events::IControlEvent>& event);
        std::shared_ptr<events::Subscription<ControlMap>> subscribe(std::function<void(ControlMap, events::Subscription<ControlMap>&)> onNotify);
        void notify();
        void update();
    };
}
}
