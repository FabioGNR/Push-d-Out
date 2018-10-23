#pragma once

#include "Theme.h"
#include <cstdio>

namespace game {
namespace themes {
    class Earth : public Theme {
    private:
        constexpr static double GRAVITY = -9.81f;
        constexpr static double FRICTION = 3.0f;

    public:
        explicit Earth(const double friction = FRICTION, const double gravity = GRAVITY)
            : Theme(friction, gravity)
        {
        }
    };
}
}
