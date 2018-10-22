#pragma once

#include "Keys.h"
#include "events/models/IControlEvent.h"
#include "KeyStates.h"
#include <map>

namespace engine {
namespace input {
    class KeyMap {
    private:
        friend class InputManager;
        std::map<Keys, KeyStates> m_map;

    public:
        KeyMap() = default;

        void update();

        void setKeyState(Keys key, KeyStates state);
        KeyStates getKeyState(Keys key) const;
        bool hasKeyState(Keys key, KeyStates state) const;
    };
}
}
