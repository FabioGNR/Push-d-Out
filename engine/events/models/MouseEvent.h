#pragma once

#include "IControlEvent.h"
#include "input/AnalogKeys.h"
#include "input/Keys.h"

namespace engine {
namespace events {
    struct MouseEvent : public IControlEvent {
        input::Keys m_key;
        int m_x;
        int m_y;
        bool m_isPressed = false;
        bool m_isAnalog = false;

        MouseEvent(int x, int y)
            : m_x(x)
            , m_y(y)
            , m_isAnalog(true)
        {
        }

        MouseEvent(int x, int y, input::Keys button, bool isPressed)
            : m_key(button)
            , m_x(x)
            , m_y(y)
            , m_isPressed(isPressed)
        {
        }
    };
}
}