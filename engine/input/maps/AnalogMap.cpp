#include "AnalogMap.h"

namespace engine {
namespace input {
    namespace maps {
        void AnalogMap::update()
        {
            keyMap.update();
        }

        void AnalogMap::setValue(engine::input::Keys key, engine::input::KeyStates state)
        {
            keyMap.setKeyState(key, state);
        }

        void AnalogMap::setValue(engine::input::AnalogKeys key, int value)
        {
            analogMap[key] = value;
        }

        KeyStates AnalogMap::getKeystate(engine::input::Keys key)
        {
            return keyMap.getKeyState(key);
        }

        int AnalogMap::getValue(engine::input::AnalogKeys key)
        {
            return analogMap[key];
        }

        bool AnalogMap::hasKeyState(engine::input::Keys key, KeyStates state)
        {
            return keyMap.hasKeyState(key, state);
        }

        bool AnalogMap::hasChanged(engine::input::AnalogKeys key)
        {
            return (analogMap[key] == 0 ? false : true);
        }
    }
}
}