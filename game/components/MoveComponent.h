#pragma once

#include <engine/ecs/Component.h>

namespace game {
namespace components {
    struct MoveComponent : public engine::ecs::BaseComponent<MoveComponent> {
        double deltaX, velocity;

        MoveComponent(double deltaX, double velocity)
            : deltaX(deltaX)
            , velocity(velocity) {};
    };
}
}