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
            const double stateDeadZone = 0.25;
            std::map<AnalogKeys, double> m_analogMap;
            std::map<AnalogKeys, States> m_analogStateMap;
            std::map<Keys, States> m_keyMap;

            void updateKeys();
            void updateAnalog();

        public:
            bool isEmpty() const;
            void update();

            void setValue(AnalogKeys key, double value);
            void setValue(Keys key, States state);

            States getState(Keys key) const;
            States getState(AnalogKeys key) const;
            double getValue(AnalogKeys key) const;

            bool hasState(Keys key, States state) const;
            bool hasState(AnalogKeys key, States state) const;
        };
    }
}
}