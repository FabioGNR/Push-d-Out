#include "RenderSystem.h"
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
    void RenderSystem::update(std::chrono::nanoseconds timeStep)
    {
        // First clear the list of rectangles
        this->rectangles.clear();
        this->sprites.clear();

        world.forEachEntityWith<PositionComponent, DimensionComponent, SpriteComponent>([&](engine::ecs::Entity& entity) {
            auto& positionComponent = world.getComponent<PositionComponent>(entity);
            auto& dimensionComponent = world.getComponent<DimensionComponent>(entity);
            auto& spriteComponent = world.getComponent<SpriteComponent>(entity);
            if (m_camera->isRectangleVisible(positionComponent.position, dimensionComponent.dimension)) {
                common::Vector2D<int> position = m_camera->translatePosition(positionComponent.position);
                common::Vector2D<int> size = m_camera->scaleSize(dimensionComponent.dimension);

                position.y = position.y - size.y;
                auto& spriteResource = spriteComponent.sprites[spriteComponent.index];
                auto scale = m_camera->scaleSize(dimensionComponent.dimension).castTo<double>();
                engine::Sprite sprite { spriteResource.spriteSheet, position + spriteResource.offset, spriteResource.size, spriteResource.position, scale };
                spriteComponent.frameTimeElapsed += timeStep;
                auto elapsedSeconds { std::chrono::duration_cast<std::chrono::milliseconds>(spriteComponent.frameTimeElapsed).count() / 1000.0 };
                if (elapsedSeconds >= spriteComponent.frameTime) {
                    spriteComponent.index++;
                    spriteComponent.index = spriteComponent.index % spriteComponent.frameCount;
                    spriteComponent.frameTimeElapsed = std::chrono::nanoseconds { 0 };
                }
                this->sprites.push_back(sprite);
            }
        });
    }

    void RenderSystem::render(engine::IRenderer& renderer)
    {
        // Draw the rectangles to the screen
        for (const auto& rectangle : this->rectangles) {
            renderer.draw(rectangle);
        }

        for (const auto& sprite : this->sprites) {
            renderer.draw(sprite);
        }
    }
}
}
