#include "AnimationSystem.h"
#include "PlayerInputSystem.h"
#include "game/components/DimensionComponent.h"
#include "game/components/PositionComponent.h"
#include "game/components/SpriteComponent.h"

#include <engine/common/Vector2D.h>

#include <engine/common/RNG.h>
#include <random>

namespace game {
namespace systems {
    using namespace components;
    void AnimationSystem::update(std::chrono::nanoseconds timeStep)
    {
        // First clear the list of sprites
        m_sprites.clear();

        m_world->forEachEntityWith<PositionComponent, DimensionComponent, SpriteComponent>([&](engine::ecs::Entity& entity) {
            auto& positionComponent = m_world->getComponent<PositionComponent>(entity);
            auto& dimensionComponent = m_world->getComponent<DimensionComponent>(entity);
            auto& spriteComponent = m_world->getComponent<SpriteComponent>(entity);
            if (m_camera->isRectangleVisible(positionComponent.position, dimensionComponent.dimension)) {
                common::Vector2D<int> position = m_camera->translatePosition(positionComponent.position);
                common::Vector2D<int> size = m_camera->scaleSize(dimensionComponent.dimension);

                position.y = position.y - size.y;
                auto& spriteResource = spriteComponent.sprites[spriteComponent.index];
                auto desiredSize = m_camera->scaleSize(dimensionComponent.dimension);
                engine::Sprite sprite{ spriteResource.spriteSheet, position + spriteResource.offset, spriteResource.size, spriteResource.position };
                sprite.setFlippedHorizontal(spriteResource.flippedHorizontal);
                sprite.setFlippedVertical(spriteResource.flippedVertical);
                sprite.setRotation(spriteResource.rotation);
                sprite.setSize(desiredSize);
                spriteComponent.frameTimeElapsed += timeStep;
                auto elapsedSeconds{ std::chrono::duration_cast<std::chrono::milliseconds>(spriteComponent.frameTimeElapsed).count() / 1000.0 };
                if (elapsedSeconds >= spriteComponent.frameTime) {
                    advanceFrame(spriteComponent);
                }
                m_sprites.push_back(sprite);
            }
        });
    }

    void AnimationSystem::render(engine::IRenderer& renderer)
    {
        // Draw the sprites to the screen
        for (const auto& sprite : m_sprites) {
            renderer.draw(sprite);
        }
    }

    void AnimationSystem::advanceFrame(components::SpriteComponent& spriteComponent)
    {
        spriteComponent.index++;
        if (spriteComponent.index >= spriteComponent.frameCount) {
            if (spriteComponent.loops) {
                spriteComponent.index = 0;
            } else {
                spriteComponent.completed = true;
            }
        }
        spriteComponent.frameTimeElapsed = std::chrono::nanoseconds{ 0 };
    }
}
}
