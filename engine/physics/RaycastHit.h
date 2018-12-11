#pragma once

#include "Body.h"

namespace engine::physics {
struct RaycastHit {
    Body* body = nullptr;
    common::Vector2D<double> point{};
    common::Vector2D<double> normal{};
    double fraction{};
};
}
