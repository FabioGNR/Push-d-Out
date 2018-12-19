#pragma once

#include <engine/common/Vector2D.h>
#include <engine/ecs/Component.h>

namespace game {
namespace components {
    struct JumpComponent : public engine::ecs::BaseComponent<JumpComponent> {
        common::Vector2D<double> delta;
        bool mayJump;

        explicit JumpComponent(common::Vector2D<double> delta)
            : delta{ delta }
            , mayJump{ true } {};
    };
}
}
