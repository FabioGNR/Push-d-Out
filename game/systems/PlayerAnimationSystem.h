#pragma once

#include <engine/ecs/World.h>
#include <game/components/SpriteComponent.h>
#include <utility>

namespace game {
namespace systems {
    class PlayerAnimationSystem : public engine::ecs::BaseSystem<PlayerAnimationSystem> {
    private:
        engine::ecs::World* m_ecsWorld;
        std::map<engine::ecs::Entity, std::map<std::string, components::SpriteComponent>> playerAnimations;

    public:
        explicit PlayerAnimationSystem(engine::ecs::World* m_ecsWorld, std::map<engine::ecs::Entity, std::map<std::string, components::SpriteComponent>> playerAnimations)
            : m_ecsWorld{ m_ecsWorld }
            , playerAnimations{ std::move(playerAnimations) }
        {
        }
        void update(std::chrono::nanoseconds timeStep) override;
        void render(engine::IRenderer& renderer) override;
    };
}
}
