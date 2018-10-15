#pragma once

#include <engine/common/Vector2D.h>
#include <engine/ecs/Component.h>

namespace game {
namespace components {
    struct DimensionComponent : public engine::ecs::BaseComponent<DimensionComponent> {
        common::Vector2D dimension;

        DimensionComponent(common::Vector2D vector)
            : dimension(vector) {};
    };
}
}
