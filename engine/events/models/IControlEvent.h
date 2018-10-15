#pragma once

#include "IEvent.h"
#include <input/Keys.h>

namespace engine {
namespace events {
    struct IControlEvent : public IEvent {
        virtual input::Keys getValue() = 0;
    };
}
}
