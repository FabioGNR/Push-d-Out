#pragma once

#include <engine/events/models/IControlEvent.h>
#include <engine/input/KeyStates.h>
#include <engine/input/Keys.h>
#include <map>

namespace engine {
namespace input {
    namespace maps {
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
}
