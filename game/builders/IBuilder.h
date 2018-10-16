#pragma once

#include <engine/ecs/World.h>
#include <engine/physics/World.h>

namespace game {
namespace builders {
    class AbstractBuilder {
    protected:
        engine::ecs::World& m_ecsWorld;
        engine::physics::World& m_physicsWorld;
    public:
        AbstractBuilder(engine::ecs::World& world, engine::physics::World& physics): m_ecsWorld(world), m_physicsWorld(physics) {};
        virtual ~AbstractBuilder() = default;
        virtual void build() const = 0;
    };
}
}
