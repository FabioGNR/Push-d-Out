#pragma once

#include "IObserver.h"
#include <queue>
#include <vector>

namespace engine {
namespace input {
    class InputManager {
    private:
        std::vector<IObserver*> observers;
        std::unique_ptr<std::map<Keys, events::IControlEvent*>> keyMap{ new std::map<Keys, events::IControlEvent*> };

    public:
        void startInput();
        void storeInput(events::IControlEvent* event);
        void subscribe(IObserver* observer);
        void notify();
    };
}
}
