#pragma once

#include "Keys.h"

#include <events/models/IControlEvent.h>
#include <map>
#include <memory>

namespace engine {
namespace input {
    class IObserver {

    public:
        virtual void update(std::map<Keys, events::IControlEvent*>& keyMap) = 0;
    };
}
}
