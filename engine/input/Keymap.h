#pragma once

#include "Keys.h"
#include "events/models/IControlEvent.h"
#include <map>

namespace engine {
namespace input {
    class Keymap {
    private:
        friend class InputManager;
        std::map<Keys, std::shared_ptr<events::IControlEvent>> m_map;

    public:
        Keymap() = default;
        void setKey(std::shared_ptr<events::IControlEvent> event);
        void removeKey(std::shared_ptr<events::IControlEvent> event);
        bool isKeyPressed(Keys key);
        bool isKeyPressed();
    };
}
}
