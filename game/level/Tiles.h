#pragma once

#include <engine/common/Vector2D.h>
#include <engine/ecs/Entity.h>
#include <engine/ecs/World.h>

namespace game::level {
class Tiles {
public:
    static engine::ecs::Entity* get(engine::ecs::World& world, common::Vector2D<int> position);
};
}
