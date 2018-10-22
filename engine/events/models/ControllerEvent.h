#pragma once

#include "IControlEvent.h"
#include "input/Keys.h"

namespace engine {
namespace events {
    struct ControllerEvent : public IControlEvent {
        input::Keys value;

        ControllerEvent(input::Keys value_)
            : value { value_ } {};
    };
}
}