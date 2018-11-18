#pragma once

#include "IControlEvent.h"
#include <input/Keys.h>

namespace engine {
namespace events {
    struct KeyDownEvent : public IControlEvent {
        input::Keys value;

        explicit KeyDownEvent(input::Keys value_)
            : value{ value_ } {};
    };
}
}
