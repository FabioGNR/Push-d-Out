#include "ControllerMap.h"

namespace engine {
namespace input {
    namespace models {
        void ControllerMap::update() {
            keyMap.update();
        }

        void ControllerMap::setValue(engine::input::Keys key, engine::input::KeyStates state) {
            keyMap.setKeyState(key, state);
        }

        void ControllerMap::setValue(engine::input::Keys key, int value) {
            test[key] = value;
        }

        KeyStates ControllerMap::getKeystate(engine::input::Keys key) {
            return keyMap.getKeyState(key);
        }

        int ControllerMap::getValue(engine::input::Keys key) {
            return test[key];
        }

        bool ControllerMap::HasState(engine::input::Keys key, KeyStates state) {
            return keyMap.hasKeyState(key, state);
        }

        bool ControllerMap::hasChanged(engine::input::Keys key) {
            return (test[key] == 0 ? false : true);
        }
    };
}
}