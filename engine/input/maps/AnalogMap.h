#pragma once

#include "KeyMap.h"
#include <engine/input/AnalogKeys.h>
#include <map>

namespace engine {
namespace input {
    namespace maps {
        class AnalogMap {
        private:
            std::map<AnalogKeys, int> analogMap;
            KeyMap keyMap {};

        public:
            void update();

            void setValue(AnalogKeys key, int value);
            void setValue(Keys key, KeyStates state);

            KeyStates getKeystate(Keys key);

            int getValue(AnalogKeys key);

            bool hasKeyState(Keys key, KeyStates state);
        };
    }
}
}