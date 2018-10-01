#pragma once

#include <engine/ecs/Component.h>

namespace game {
namespace components {
    struct JumpComponent : public engine::BaseComponent<JumpComponent> {
        double deltaY, velocity;

        JumpComponent(double deltaY, double velocity)
            : deltaY(deltaY)
            , velocity(velocity) {};
    };
}
}
