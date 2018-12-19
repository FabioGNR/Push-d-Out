#pragma once

#include "Body.h"

namespace engine {
namespace physics {
    struct Contact {
        common::Vector2D<double> point;
        Body* a = nullptr;
        Body* b = nullptr;
    };
}
}
