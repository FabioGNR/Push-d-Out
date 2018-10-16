#pragma once

#include "engine/ecs/System.h"
#include "engine/physics/World.h"
#include <ecs/World.h>

namespace game {
namespace systems {
    class WeaponSystem : public engine::ecs::BaseSystem<WeaponSystem> {
        engine::ecs::World& m_ecsWorld;
        engine::physics::World& m_physicsWorld;

    public:
        WeaponSystem(engine::ecs::World& m_ecsWorld, engine::physics::World& m_physicsWorld)
            : m_ecsWorld(m_ecsWorld)
            , m_physicsWorld(m_physicsWorld) {};

        void update(std::chrono::nanoseconds timeStep) override;
        void render(engine::IRenderer& renderer) override;
    };
}
}
