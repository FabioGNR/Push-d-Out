#pragma once

#include "KeyMap.h"
#include "input/Keys.h"
#include <map>

namespace engine {
namespace input {
    namespace models {
        class ControllerMap {
        private:
            std::map<Keys, int> test;
            KeyMap keyMap;

        public:
            void update();
            void setValue(Keys key, int value);
            void setValue(Keys key, KeyStates state);

            KeyStates getKeystate(Keys key);
            int getValue(Keys key);

            bool HasState(Keys key, KeyStates state);
            bool hasChanged(Keys key);
        };
    }
}
}
