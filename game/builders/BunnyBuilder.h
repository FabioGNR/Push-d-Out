#pragma once

#include <engine/ecs/Entity.h>
#include <engine/ecs/World.h>
#include <engine/physics/World.h>
#include <game/components/DimensionComponent.h>
#include <game/components/PositionComponent.h>

namespace game::builders {
class BunnyBuilder {
private:
    engine::ecs::Entity* m_entity;
    engine::ecs::World* m_world;
    engine::physics::World* m_physics;

    common::Vector2D<double> m_position{ 0, 0 };
    common::Vector2D<double> m_dimensions{ 1, 1 };

public:
    explicit BunnyBuilder(engine::ecs::World* w, engine::physics::World* p);
    BunnyBuilder& setPosition(common::Vector2D<double>);
    BunnyBuilder& setDimensions(common::Vector2D<double>);
    engine::ecs::Entity* build();
};
}
