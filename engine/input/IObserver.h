#pragma once

#include "Keys.h"

#include <events/models/IControlEvent.h>
#include <map>
#include <memory>

namespace engine {
namespace input {
    class IObserver {
    public:
        virtual void onInputUpdate(std::map<Keys, std::shared_ptr<events::IControlEvent>>& keymap) = 0;
    };
}
}
