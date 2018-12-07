#pragma once

#include "engine/ecs/Component.h"

namespace game {
namespace components {
    struct DirectionComponent : public engine::ecs::BaseComponent<DirectionComponent> {
        enum class Direction {
            LEFT = -1,
            RIGHT = 1
        };
        Direction direction = Direction::RIGHT;
    };
}
}