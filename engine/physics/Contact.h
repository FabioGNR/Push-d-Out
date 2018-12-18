#pragma once

#include "Body.h"

namespace engine {
namespace physics {
    class Contact {
    public:
        virtual ~Contact() = default;

        std::vector<common::Vector2D<double>> points;
        common::Vector2D<double> normal;
        Body* a = nullptr;
        Body* b = nullptr;

        virtual void setEnabled(bool enabled) = 0;
    };
}
}
