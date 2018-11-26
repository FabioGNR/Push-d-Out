#include "InputMap.h"

namespace engine {
namespace input {
    namespace maps {
        void InputMap::update()
        {
            auto it = m_keyMap.begin();
            while (it != m_keyMap.end()) {
                switch (it->second) {
                case KeyStates::PRESSED:
                    it->second = KeyStates::DOWN;
                    ++it;
                    break;
                case KeyStates::DOWN:
                    ++it;
                    break;
                case KeyStates::UP:
                case KeyStates::PRESSED_AND_RELEASED:
                case KeyStates::RELEASED:
                    it = m_keyMap.erase(it);
                    break;
                }
            }
        }

        void InputMap::setValue(engine::input::Keys key, engine::input::KeyStates state)
        {
            if (key == Keys::UNKNOWN) {
                return;
            }

            if (getKeyState(key) == PRESSED && state == RELEASED) {
                m_keyMap[key] = PRESSED_AND_RELEASED;
            } else {
                m_keyMap[key] = state;
            }
        }

        void InputMap::setValue(engine::input::AnalogKeys key, int value)
        {
            if (key == AnalogKeys::CON_UNKNOWN) {
                return;
            }
            m_analogMap[key] = value;
        }

        KeyStates InputMap::getKeyState(engine::input::Keys key)
        {
            if (m_keyMap.find(key) == m_keyMap.end()) {
                return KeyStates::UP;
            }
            return m_keyMap.at(key);
        }

        int InputMap::getValue(engine::input::AnalogKeys key)
        {
            if (m_analogMap.find(key) == m_analogMap.end()) {
                return 0;
            }
            return m_analogMap.at(key);
        }

        bool InputMap::hasKeyState(engine::input::Keys key, KeyStates state)
        {
            return ((getKeyState(key) & state) == state);
        }
    }
}
}