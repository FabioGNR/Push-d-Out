#include "KeyMap.h"

namespace engine {
namespace input {

    // everything that was PRESSED, is now DOWN
    // everything that was DOWN, is still DOWN
    // everything that was RELEASED, is now UP, thus removed from the map
    void KeyMap::update()
    {
        auto it = m_map.begin();
        while (it != m_map.end()) {
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
                it = m_map.erase(it);
                break;
            }
        }
    }

    void KeyMap::setKeyState(Keys key, KeyStates state)
    {
        if (getKeyState(key) == PRESSED && state == RELEASED) {
            m_map[key] = PRESSED_AND_RELEASED;
        } else {
            m_map[key] = state;
        }
    }

    /*
     * Returns true when result equals request, see `KeyStates.h` for more info.
     */
    bool KeyMap::hasKeyState(Keys key, KeyStates state) const
    {
        return ((getKeyState(key) & state) == state);
    }

    KeyStates KeyMap::getKeyState(Keys key) const
    {
        if (m_map.find(key) == m_map.end()) {
            return KeyStates::UP;
        }
        return m_map.at(key);
    }
}
}
