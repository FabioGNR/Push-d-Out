#pragma once

#include <engine/ecs/World.h>
#include <engine/physics/World.h>

namespace game::ai {
class Behaviour {
protected:
    engine::ecs::World* m_world;
    engine::physics::World* m_physics;
    engine::ecs::Entity* m_entity;

public:
    Behaviour(engine::ecs::World* world, engine::physics::World* physics, engine::ecs::Entity* entity)
        : m_world{ world }
        , m_physics{ physics }
        , m_entity{ entity } {};

    virtual ~Behaviour() = default;
    virtual void act(std::chrono::nanoseconds) = 0;
    virtual void init() = 0;
    virtual void exit() = 0;
};
}