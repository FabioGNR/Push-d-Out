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
    void RenderSystem::update(std::chrono::nanoseconds /* timeStep */)
    {
        // First clear the list of rectangles
        this->rectangles.clear();

        // Iterate through the components and draw the necessary shapes
        world.forEachEntityWith<components::PositionComponent, components::DimensionComponent>([&](engine::ecs::Entity& entity) {
            auto& positionComponent = world.getComponent<components::PositionComponent>(entity);
            auto& dimensionComponent = world.getComponent<components::DimensionComponent>(entity);
            if (m_camera->isRectangleVisible(positionComponent.position, dimensionComponent.dimension)) {
                common::Vector2D<int> position = m_camera->translatePosition(positionComponent.position);
                common::Vector2D<int> size = m_camera->scaleSize(dimensionComponent.dimension);
                engine::Color color{
                    common::RNG::generate(0, 255),
                    common::RNG::generate(0, 255),
                    common::RNG::generate(0, 255),
                    100
                };
                // because rendering is done from the top, while the box is bottom, shift the y position
                position.y = position.y - size.y;
                engine::RectangleShape shape{ position, size, color };

                this->rectangles.push_back(shape);
            }
        });
    }

    void RenderSystem::render(engine::IRenderer& renderer)
    {
        // Draw the rectangles to the screen
        for (const auto& rectangle : this->rectangles) {
            renderer.draw(rectangle);
        }
    }
}
}
