#pragma once

#include "KeyMap.h"
#include "OtherMap.h"

namespace engine {
namespace input {

    class ControlMap {
    private:
        KeyMap keyMap;
        OtherMap otherMap;

    public:
        void setAxisValue(Keys key, int axisValue);
        int getAxisValue(Keys key);
        bool axisChanged(Keys key);
        void setKeyState(Keys key, KeyStates state);
        bool hasKeyState(Keys key, KeyStates state) const;
        KeyStates getKeyState(Keys key) const;
        void update();
    };

}
}
