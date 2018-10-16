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
            case KeyStates::RELEASED:
                it = m_map.erase(it);
                break;
            }
        }
    }

    void KeyMap::setKeyState(Keys key, KeyStates state)
    {
        m_map.insert(std::pair<Keys, KeyStates>(key, state));
    }

    KeyStates KeyMap::getKeyState(Keys key)
    {
        if (m_map.find(key) == m_map.end()) {
            return KeyStates::UP;
        }
        return m_map.at(key);
    }
}
}
