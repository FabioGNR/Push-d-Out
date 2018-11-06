#pragma once

#include "events/models/ControllerEvent.h"
#include <map>

namespace engine {
namespace input {
    class OtherMap {
    private:
        std::map<Keys, int> test;

    public:
        OtherMap() = default;

        void add(Keys key, int axisValue);
        int getAxesValue(Keys key);
        void update();
        bool axisChanged(Keys key);
    };
}
}
