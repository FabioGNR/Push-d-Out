#include "PlayerAnimationSystem.h"
#include <game/components/AnimationsComponent.h>
#include <game/components/BodyComponent.h>
#include <game/components/DirectionComponent.h>
#include <game/components/MoveComponent.h>
#include <game/components/PlayerInputComponent.h>
#include <game/components/PositionComponent.h>

namespace game {
namespace systems {

    void PlayerAnimationSystem::update(std::chrono::nanoseconds /* timeStep */)
    {
        m_ecsWorld->forEachEntityWith<components::PositionComponent,
            components::BodyComponent,
            components::SpriteComponent,
            components::AnimationsComponent,
            components::DirectionComponent>([&](engine::ecs::Entity& entity) {
            auto& spriteComponent = m_ecsWorld->getComponent<components::SpriteComponent>(entity);
            if (spriteComponent.loops || spriteComponent.completed) {
                setCurrentPlayerAnimation(entity, spriteComponent);
            }
            updatePlayerSpriteDirection(entity, spriteComponent);
        });
    }

    void PlayerAnimationSystem::render(engine::IRenderer& /*renderer*/)
    {
    }

    void PlayerAnimationSystem::setCurrentPlayerAnimation(engine::ecs::Entity& player,
        components::SpriteComponent& spriteComponent)
    {
        const auto& animations = m_ecsWorld->getComponent<components::AnimationsComponent>(player).animations;
        auto& bodyComponent = m_ecsWorld->getComponent<components::BodyComponent>(player);
        std::string nextAnimationName = determineAnimationFromVelocity(bodyComponent.body->getLinearVelocity());
        if (nextAnimationName.length() == 0) {
            return;
        }
        const auto& nextSpriteComponent = animations.find(nextAnimationName);
        if (nextSpriteComponent != animations.end()) {
            if (spriteComponent != nextSpriteComponent->second) {
                spriteComponent = nextSpriteComponent->second;
            }
        }
    }

    void PlayerAnimationSystem::updatePlayerSpriteDirection(engine::ecs::Entity& player,
        components::SpriteComponent& spriteComponent)
    {
        auto& directionComponent = m_ecsWorld->getComponent<components::DirectionComponent>(player);
        // flip player sprite for current direction
        spriteComponent.flippedHorizontal = directionComponent.direction == components::DirectionComponent::Direction::LEFT;
    }

    std::string PlayerAnimationSystem::determineAnimationFromVelocity(const common::Vector2D<double>& velocity) const
    {
        if (velocity.y == 0) {
            if (velocity.x != 0) {
                return "Walking";
            } else {
                return "Idle";
            }
        } else {
            return "Jumping";
        }
    }
}
}