#pragma once

#include "IControlEvent.h"

namespace engine {
namespace events {
    struct KeyEvent : public IControlEvent {
    private:
        input::Keys m_value;
        bool m_pressed;

    public:
        KeyEvent(input::Keys value, bool pressed)
            : m_value{ value }
            , m_pressed{ pressed } {};

        input::Keys getValue() override;
    };
}
}
