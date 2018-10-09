#pragma once

#include <engine/ecs/Component.h>

namespace game {
namespace components {
    struct DimensionComponent : public engine::ecs::BaseComponent<DimensionComponent> {
        double width, height;

        DimensionComponent(double width, double height)
            : width(width)
            , height(height) {};
    };
}
}
