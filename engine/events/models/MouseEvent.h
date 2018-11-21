#pragma once

#include "IControlEvent.h"
#include "input/AnalogKeys.h"
#include "input/Keys.h"

namespace engine {
namespace events {
    struct MouseEvent : public IControlEvent {
        int m_x;
        int m_y;
        input::Keys m_key;
        bool m_isPressed;
        bool m_isAnalog = false;

        MouseEvent(int x, int y)
            : m_x(x)
            , m_y(y)
            , m_isPressed(true)
        {
        }

        MouseEvent(input::Keys button)
            : m_key(button)
        {
        }
    };
}
}