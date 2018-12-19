#pragma once

#include <engine/common/Vector2D.h>
#include <engine/ecs/Component.h>

namespace game {
namespace components {
    struct MoveComponent : public engine::ecs::BaseComponent<MoveComponent> {
        common::Vector2D<double> delta;

        explicit MoveComponent(common::Vector2D<double> delta)
            : delta{ delta } {};
    };
}
}