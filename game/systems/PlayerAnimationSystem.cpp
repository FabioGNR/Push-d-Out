#include "PlayerAnimationSystem.h"
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
            components::PlayerInputComponent,
            components::SpriteComponent,
            components::DirectionComponent>([&](engine::ecs::Entity& entity) {
            auto& bodyComponent = m_ecsWorld->getComponent<components::BodyComponent>(entity);
            auto& spriteComponent = m_ecsWorld->getComponent<components::SpriteComponent>(entity);
            auto& directionComponent = m_ecsWorld->getComponent<components::DirectionComponent>(entity);
            const auto& animationsPair = playerAnimations.find(entity);
            if (animationsPair == playerAnimations.end()) {
                return;
            }
            auto animations = animationsPair->second;
            const auto playerVelocity = bodyComponent.body->getLinearVelocity();
            if (playerVelocity.y == 0) {
                if (playerVelocity.x != 0) {
                    const auto& walkingSpriteComponent = animations.find("Walking");
                    if (walkingSpriteComponent == animations.end()) {
                        return;
                    }
                    if (spriteComponent != walkingSpriteComponent->second) {
                        spriteComponent = walkingSpriteComponent->second;
                    }
                } else {
                    const auto& idleSpriteComponent = animations.find("Idle");
                    if (idleSpriteComponent == animations.end()) {
                        return;
                    }
                    if (spriteComponent != idleSpriteComponent->second) {
                        spriteComponent = idleSpriteComponent->second;
                    }
                }
            } else {
                const auto& jumpingSpriteComponent = animations.find("Jumping");
                if (jumpingSpriteComponent == animations.end()) {
                    return;
                }
                spriteComponent = jumpingSpriteComponent->second;
            }

            std::for_each(spriteComponent.sprites.begin(), spriteComponent.sprites.end(), [&](auto& sprite) {
                sprite.flippedHorizontal = directionComponent.direction == components::DirectionComponent::Direction::LEFT;
            });
        });
    }

    void PlayerAnimationSystem::render(engine::IRenderer& /*renderer*/)
    {
    }
}
}