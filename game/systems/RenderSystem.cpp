#include "RenderSystem.h"
#include "PlayerInputSystem.h"
#include <common/Vector2D.h>
#include <game/components/DimensionComponent.h>
#include <game/components/PositionComponent.h>
#include <game/components/SpriteComponent.h>
#include <random>

namespace game {
namespace systems {
    void RenderSystem::update(std::chrono::nanoseconds /* timeStep */)
    {
        world.forEachEntityWith<components::PositionComponent, components::DimensionComponent>([&](engine::ecs::Entity& entity) {
            auto& positionComponent = world.getComponent<components::PositionComponent>(entity);
            auto& dimensionComponent = world.getComponent<components::DimensionComponent>(entity);

            common::Vector2D<int> position{static_cast<int>(positionComponent.position.x * m_unitSize),
                                           static_cast<int>(positionComponent.position.y * m_unitSize) };
            common::Vector2D<int> size{static_cast<int>(dimensionComponent.dimension.x * m_unitSize),
                                       static_cast<int>(dimensionComponent.dimension.y * m_unitSize) };
            engine::Color color{ rand() % 255, rand() % 255, rand() % 255, 100 };

            engine::RectangleShape shape{ position, size, color };

            this->rectangles.push_back(shape);
        });
    }

    void RenderSystem::render(engine::IRenderer& renderer)
    {
        for (const auto& rectangle : this->rectangles) {
            renderer.draw(rectangle);
        }
    }
}
}
