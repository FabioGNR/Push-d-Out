#pragma once

#include "IControlEvent.h"
#include "input/AnalogKeys.h"
#include "input/Keys.h"

namespace engine {
namespace events {
    struct ControllerEvent : public IControlEvent {
        input::AnalogKeys m_analogKey;
        input::Keys m_key;
        int m_axisValue;
        int m_ID;
        bool m_keyDown;

        ControllerEvent(input::Keys key, bool keyDown, int ID)
            : m_key { key }
            , m_ID(ID)
            , m_keyDown { keyDown } {};

        ControllerEvent(input::AnalogKeys analogKey, int axisValue, int ID)
            : m_analogKey(analogKey)
            , m_axisValue(axisValue)
            , m_ID(ID) {};
    };
}
}