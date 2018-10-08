#pragma once

#include <engine/ecs/Component.h>

namespace game {
namespace components {
    struct SpriteComponent : public engine::BaseComponent<SpriteComponent> {
        double width, height, x, y;

        SpriteComponent(double width, double height, double x, double y)
            : width(width)
            , height(height)
            , x(x)
            , y(y) {};
    };
}
}
