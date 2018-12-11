#pragma once

#include <engine/ecs/World.h>
#include <game/components/SpriteComponent.h>
#include <utility>

namespace game {
namespace systems {
    class PlayerAnimationSystem : public engine::ecs::BaseSystem<PlayerAnimationSystem> {
    private:
        engine::ecs::World* m_ecsWorld;

        std::string determineAnimationFromVelocity(const common::Vector2D<double>& velocity) const;
        void setCurrentPlayerAnimation(engine::ecs::Entity& player, components::SpriteComponent& spriteComponent);
        void updatePlayerSpriteDirection(engine::ecs::Entity& player, components::SpriteComponent& spriteComponent);

    public:
        explicit PlayerAnimationSystem(engine::ecs::World* m_ecsWorld)
            : m_ecsWorld{ m_ecsWorld }
        {
        }
        void update(std::chrono::nanoseconds timeStep) override;
        void render(engine::IRenderer& renderer) override;
    };
}
}
