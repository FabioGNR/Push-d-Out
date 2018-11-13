#pragma once

#include "IControlEvent.h"
#include <input/Keys.h>

namespace engine {
namespace events {
    struct KeyUpEvent : public IControlEvent {
        input::Keys value;

        explicit KeyUpEvent(input::Keys value_)
            : value{ value_ } {};
    };
}
}
