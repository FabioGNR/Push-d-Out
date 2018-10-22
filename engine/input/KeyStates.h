#pragma once

namespace engine {
namespace input {
    enum KeyStates {
        PRESSED = 1,
        PRESSED_AND_RELEASED = 5,
        DOWN = 2,
        RELEASED = 4,
        UP = 8
    };
}
}
