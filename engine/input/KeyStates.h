#pragma once

namespace engine {
namespace input {
    /*
     *              8 4 2 1
     * DOWN         0 0 1 0
     * PRESSED      0 0 1 1
     * RELEASED     0 1 0 0
     * PRESSED/REL. 0 1 1 1
     * UP           1 1 0 0
     *
     * Returns true when result equals request, e.g.
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
     * UP           | RELEASED      | true          | 0100
     * etc...
     */
    enum KeyStates {
        DOWN = 2,
        PRESSED = 3,
        RELEASED = 4,
        PRESSED_AND_RELEASED = 7,
        UP = 12
    };
}
}
