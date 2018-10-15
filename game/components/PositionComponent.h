#pragma once

#include <engine/common/Vector2D.h>
#include <engine/ecs/Component.h>

namespace game {
namespace components {
    struct PositionComponent : public engine::ecs::BaseComponent<PositionComponent> {
        common::Vector2D<double> position;

        PositionComponent(common::Vector2D<double> vector)
            : position(vector) {};
    };
}
}
