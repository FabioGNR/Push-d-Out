#pragma once

#include "Theme.h"

namespace game {
namespace themes {
    class Moon : public Theme {
    private:
        constexpr static double GRAVITY = -1.6f;
        constexpr static double FRICTION = 0.5f;

    public:
        explicit Moon(const double friction = FRICTION, const double gravity = GRAVITY)
            : Theme(friction,
                  gravity)
        {
        }
    };
}
}
