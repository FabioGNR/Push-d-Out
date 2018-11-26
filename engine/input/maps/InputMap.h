#pragma once

#include <engine/input/AnalogKeys.h>
#include <map>
#include <engine/input/KeyStates.h>
#include <engine/input/Keys.h>

namespace engine {
namespace input {
    namespace maps {
        class InputMap {
        private:
            std::map<Keys, KeyStates> m_keyMap;
            std::map<AnalogKeys, int> m_analogMap;

        public:
            void update();

            void setValue(AnalogKeys key, int value);
            void setValue(Keys key, KeyStates state);
            KeyStates getKeyState(Keys key);
            int getValue(AnalogKeys key);
            bool hasKeyState(Keys key, KeyStates state);

        };
    }
}
}