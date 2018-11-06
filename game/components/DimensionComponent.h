#pragma once

#include <engine/common/Vector2D.h>
#include <engine/ecs/Component.h>

namespace game {
namespace components {
    struct DimensionComponent : public engine::ecs::BaseComponent<DimensionComponent> {
        common::Vector2D<double> dimension;

        explicit DimensionComponent(common::Vector2D<double> vector)
            : dimension(vector){};
    };
}
}
