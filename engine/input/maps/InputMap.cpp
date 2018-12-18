#include "InputMap.h"
#include <iostream>

namespace engine {
namespace input {
    namespace maps {
        void InputMap::update()
        {
            updateKeys();
            updateAnalog();
        }

        void InputMap::updateAnalog()
        {
            auto it = m_analogStateMap.begin();
            while (it != m_analogStateMap.end()) {
                switch (it->second) {
                case States::PRESSED:
                    it->second = States::DOWN;
                    ++it;
                    break;
                case States::DOWN:
                    ++it;
                    break;
                case States::UP:
                case States::PRESSED_AND_RELEASED:
                case States::RELEASED:
                    it = m_analogStateMap.erase(it);
                    break;
                }
            }
        }

        void InputMap::updateKeys()
        {
            auto it = m_keyMap.begin();
            while (it != m_keyMap.end()) {
                switch (it->second) {
                case States::PRESSED:
                    it->second = States::DOWN;
                    ++it;
                    break;
                case States::DOWN:
                    ++it;
                    break;
                case States::UP:
                case States::PRESSED_AND_RELEASED:
                case States::RELEASED:
                    it = m_keyMap.erase(it);
                    break;
                }
            }
        }

        void InputMap::setValue(const Keys key, const States state)
        {
            if (key == Keys::UNKNOWN) {
                return;
            }

            if (getState(key) == PRESSED && state == RELEASED) {
                m_keyMap[key] = PRESSED_AND_RELEASED;
            } else {
                m_keyMap[key] = state;
            }
        }

        bool InputMap::isEmpty() const
        {
            return m_analogMap.empty() && m_analogStateMap.empty() && m_keyMap.empty();
        }

        void InputMap::setValue(const engine::input::AnalogKeys key, const double value)
        {
            if (key == AnalogKeys::CON_UNKNOWN) {
                return;
            }
            m_analogMap[key] = value;

            States state = std::abs(value) < stateDeadZone ? RELEASED : PRESSED;

            if (getState(key) == PRESSED && state == RELEASED) {
                m_analogStateMap[key] = PRESSED_AND_RELEASED;
            } else {
                m_analogStateMap[key] = m_analogStateMap[key] == DOWN && state == PRESSED ? DOWN : state;
            }
        }

        States InputMap::getState(Keys key) const
        {
            if (m_keyMap.find(key) == m_keyMap.end()) {
                return States::UP;
            }
            return m_keyMap.at(key);
        }

        States InputMap::getState(AnalogKeys key) const
        {
            if (m_analogStateMap.find(key) == m_analogStateMap.end()) {
                return States::UP;
            }
            return m_analogStateMap.at(key);
        }

        double InputMap::getValue(const AnalogKeys key) const
        {
            if (m_analogMap.find(key) == m_analogMap.end()) {
                return 0;
            }
            return m_analogMap.at(key);
        }

        bool InputMap::hasState(Keys key, States state) const
        {
            return ((getState(key) & state) == state);
        }

        bool InputMap::hasState(AnalogKeys key, States state) const
        {
            return ((getState(key) & state) == state);
        }
    }
}
}