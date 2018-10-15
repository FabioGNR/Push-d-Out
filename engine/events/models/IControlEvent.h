#pragma once

#include "IEvent.h"
#include <input/Keys.h>

namespace engine {
namespace events {
    class IControlEvent : public IEvent {
    public:
        virtual input::Keys getValue() = 0;
    };
}
}
