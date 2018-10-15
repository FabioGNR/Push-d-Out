#pragma once

#include "IObserver.h"
#include <queue>
#include <vector>

namespace engine {
namespace input {
    class InputManager {
    private:
        std::vector<IObserver*> observers;
        std::unique_ptr<std::map<Keys, std::shared_ptr<events::IControlEvent>>> m_keymap{ new std::map<Keys, std::shared_ptr<events::IControlEvent>> };

    public:
        void startInput();
        void storeInput(std::shared_ptr<events::IControlEvent> event);
        void subscribe(IObserver* observer);
        void notify();
    };
}
}
