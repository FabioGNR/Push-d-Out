#pragma once

#include "IBuilder.h"
#include <engine/physics/World.h>

namespace game {
namespace builders {
    class CharacterBuilder : public IBuilder {
    protected:
        engine::ecs::World& m_ecsWorld;
        engine::physics::World& m_physicsWorld;

    public:
        CharacterBuilder(engine::ecs::World& world, engine::physics::World& physics)
            : m_ecsWorld(world)
            , m_physicsWorld(physics)
        {
        }
        void build() const override;
    };
}
}
