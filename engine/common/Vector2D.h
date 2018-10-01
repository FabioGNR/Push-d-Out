#pragma once

namespace common {
    struct Vector2D {
        double x;
        double y;

        explicit Vector2D(double x_, double y_)
            : x{ x_ }
            , y{ y_ }
        {
        }
    };
}
