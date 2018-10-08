#pragma once

#include <cstdio>

namespace game {
namespace themes {
    class Theme {
    private:
        double _friction;
        double _gravity;

    public:
        Theme(double friction, double gravity)
            : _friction{ friction }
            , _gravity{ gravity } {};

        double getGravity() const;
        double getFriction() const;
    };
}
}
