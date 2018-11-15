#pragma once

#include "IControlEvent.h"
#include "input/AnalogKeys.h"
#include "input/Keys.h"

namespace engine {
namespace events {
    struct ControllerEvent : public IControlEvent {
        int m_ID;
        input::Keys m_key;
        input::AnalogKeys m_analogKey;
        int m_axisValue;
        bool m_keyDown;
        bool m_isAnalog = false;

        ControllerEvent(int ID, input::Keys key, bool keyDown)
            : m_ID(ID)
            , m_key { key }
            , m_keyDown { keyDown } {};

        ControllerEvent(int ID, input::AnalogKeys analogKey, int axisValue)
            : m_ID(ID)
            , m_analogKey(analogKey)
            , m_axisValue(axisValue)
            , m_isAnalog(true){};
    };
}
}