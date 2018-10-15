#pragma once

#include <engine/common/Vector2D.h>
#include <engine/ecs/Component.h>

namespace game {
namespace components {
    struct PositionComponent : public engine::ecs::BaseComponent<PositionComponent> {
        common::Vector2D position;

        PositionComponent(common::Vector2D vector)
            : position(vector) {};
    };
}
}
