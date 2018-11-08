#pragma once

#include "maps/ControllerMap.h"
#include "events/models/Subscription.h"
#include <events/models/ControllerEvent.h>
#include <events/models/KeyDownEvent.h>
#include <events/models/KeyUpEvent.h>
#include <input/maps/ControllerMap.h>
#include <memory>
//#include <queue>
#include <vector>

namespace engine {
namespace input {
    class InputManager {
    private:
        std::vector<std::weak_ptr<events::Subscription<ControllerMap>>> m_subscriptions;
        ControllerMap controlMap;
        std::map<int, std::shared_ptr<ControllerMap>> conList;

    public:
        void handle(const std::shared_ptr<events::IControlEvent>& event);
        std::shared_ptr<events::Subscription<ControllerMap>> subscribe(std::function<void(ControllerMap, events::Subscription<ControllerMap>&)> onNotify);
        void notify();
        void update();
        //const KeyMap& getKeyMap() const;
    };
}
}
