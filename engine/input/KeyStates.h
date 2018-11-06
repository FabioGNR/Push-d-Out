#pragma once

namespace engine {
namespace input {
    /*
     *
     * Returns true when result equals request, e.g.
     * See unit test KeyMap_test.cpp for all expectations
     *
     * ACTUAL STATE | REQUEST       | RETURNS       | STATE & REQUEST
     * -------------|---------------|---------------|---------------
     * DOWN         | DOWN          | true          | 0010
     * DOWN         | PRESSED       | false         | 0010
     * DOWN         | RELEASED      | false         | 0000
     * DOWN         | PRESSED/REL.  | false         | 0010
     * DOWN         | UP            | false         | 0000
     * PRESSED      | DOWN          | true          | 0010
     * RELEASED     | DOWN          | false         | 0000
     * PRESSED/REL. | DOWN          | true          | 0010
     * RELEASED     | UP            | true          | 0100
     * etc...
     */
    enum KeyStates {
        DOWN = 0b0010,
        PRESSED = 0b0011,
        UP = 0b0100,
        RELEASED = 0b1100,
        PRESSED_AND_RELEASED = 0b1111
    };
}
}
