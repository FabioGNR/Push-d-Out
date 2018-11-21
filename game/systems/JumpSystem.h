#pragma once

#include <engine/ecs/System.h>
#include <engine/ecs/World.h>
#include <engine/physics/ContactListener.h>
#include <engine/physics/World.h>
#include <game/listeners/JumpContactListener.h>

namespace game {
namespace systems {
    class JumpSystem : public engine::ecs::BaseSystem<JumpSystem> {
    private:
        engine::ecs::World& m_world;

    public:
        explicit JumpSystem(engine::ecs::World& world, engine::physics::World& m_physicsWorld)
            : m_world{ world }
        {
            m_physicsWorld.addContactListener(std::make_unique<listeners::JumpContactListener>(world));
        };

        void update(std::chrono::nanoseconds timeStep) override;
        void render(engine::IRenderer& renderer) override;
    };
}
}
