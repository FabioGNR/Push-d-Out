#include "ControlMap.h"

namespace engine {
namespace input {
    void ControlMap::update()
    {
        keyMap.update();
    }

    void ControlMap::setKeyState(engine::input::Keys key, engine::input::KeyStates state)
    {
        keyMap.setKeyState(key, state);
    }

    bool ControlMap::hasKeyState(engine::input::Keys key, engine::input::KeyStates state) const
    {
        return keyMap.hasKeyState(key, state);
    }

    KeyStates ControlMap::getKeyState(engine::input::Keys key) const {
        return keyMap.getKeyState(key);
    }

    void ControlMap::setAxisValue(engine::input::Keys key, int axisValue) {
        otherMap.add(key, axisValue);
    }

    int ControlMap::getAxisValue(engine::input::Keys key) {
        return otherMap.getAxesValue(key);
    }

    bool ControlMap::axisChanged(engine::input::Keys key) {
        return otherMap.axisChanged(key);
    }
}
}