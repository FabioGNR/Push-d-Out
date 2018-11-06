#pragma once

#include "IControlEvent.h"
#include "input/Keys.h"

namespace engine {
namespace events {
    struct ControllerEvent : public IControlEvent {
        input::Keys value;
        int axisValue;
        bool keyDown;
        int ID;

        ControllerEvent(input::Keys value_, bool keyDown_, int ID_)
            : value { value_ }
            , keyDown(keyDown_)
            , ID(ID_) {};

        ControllerEvent(input::Keys value_, int axis_, int ID_)
            : value(value_)
            , axisValue(axis_)
            , ID(ID_) {};
    };
}
}