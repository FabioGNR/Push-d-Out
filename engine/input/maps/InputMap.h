#pragma once

#include <engine/input/AnalogKeys.h>
#include <engine/input/Keys.h>
#include <engine/input/States.h>
#include <map>

namespace engine {
namespace input {
    namespace maps {
        class InputMap {
        private:
            const int stateDeadZone = 7500;
            std::map<AnalogKeys, int> m_analogMap;
            std::map<AnalogKeys, States> m_analogStateMap;
            std::map<Keys, States> m_keyMap;

            void updateKeys();
            void updateAnalog();

        public:
            bool changed = false;

            void update();

            void setValue(AnalogKeys key, int value);
            void setValue(Keys key, States state);

            States getState(Keys key) const;
            States getState(AnalogKeys key) const;
            int getValue(AnalogKeys key) const;

            bool hasState(Keys key, States state) const;
            bool hasState(AnalogKeys key, States state) const;
        };
    }
}
}