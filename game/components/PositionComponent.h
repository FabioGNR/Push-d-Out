#pragma once

#include <engine/ecs/Component.h>

namespace game {
namespace components {
    struct PositionComponent : public engine::BaseComponent<PositionComponent> {
        double x, y;

        PositionComponent(double x, double y)
            : x(x)
            , y(y) {};
    };
}
}
