#pragma once
#include <engine/ecs/Entity.h>
#include <engine/ecs/System.h>
#include <engine/ecs/World.h>
#include <engine/physics/World.h>
#include <engine/sound/ISoundManager.h>

namespace game {
namespace systems {
    namespace items {
        class ReverseGravitySystem : public engine::ecs::BaseSystem<ReverseGravitySystem> {
            engine::ecs::World& m_ecsWorld;
            engine::physics::World& m_physicsWorld;

        public:
            ReverseGravitySystem(engine::ecs::World& ecsWorld, engine::physics::World& physicsWorld,
                engine::sound::ISoundManager* soundManager);

            void update(std::chrono::nanoseconds timeStep) override;

            void render(engine::IRenderer& renderer) override;

        private:
            engine::sound::ISoundManager* m_soundManager{};
            static constexpr double DURATION_SECONDS = 2.0;

            void reverseGravity();
        };
    }
}
}
