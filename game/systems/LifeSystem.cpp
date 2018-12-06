#include "LifeSystem.h"
#include <engine/common/RNG.h>
#include <game/builders/CharacterSpawnGenerator.h>
#include <game/components/BodyComponent.h>
#include <game/components/DimensionComponent.h>
#include <game/components/EquipmentComponent.h>
#include <game/components/InventoryComponent.h>
#include <game/components/ItemComponent.h>
#include <game/components/LifeComponent.h>
#include <game/components/PositionComponent.h>

namespace game {
namespace systems {
    void LifeSystem::update(std::chrono::nanoseconds /*timeStep*/)
    {
        const int range = -5;

        m_world->forEachEntityWith<components::LifeComponent,
            components::PositionComponent,
            components::DimensionComponent>([&](engine::ecs::Entity& entity) {
            auto& position = m_world->getComponent<components::PositionComponent>(entity).position;
            auto& dimension = m_world->getComponent<components::DimensionComponent>(entity).dimension;
            auto& body = *m_world->getComponent<components::BodyComponent>(entity).body;

            if ((position.y + dimension.y) < range && !m_camera->isRectangleVisible(position, dimension)) {
                int& lifeCounter = m_world->getComponent<components::LifeComponent>(entity).count;

                if (lifeCounter > 0) {
                    lifeCounter -= 1;

                    m_world->removeComponent<components::EquipmentComponent>(entity);
                    m_world->removeComponent<components::ItemComponent>(entity);
                    m_world->removeComponent<components::InventoryComponent>(entity);

                    // Add an empty
                    components::InventoryComponent inventoryComponent{};
                    m_world->addComponent<components::InventoryComponent>(entity, inventoryComponent);

                    auto positions = builders::CharacterSpawnGenerator::collect(*m_world);
                    int randomValue = common::RNG::generate(1, static_cast<int>(positions.size()));
                    const auto newPosition = positions[randomValue - 1];

                    if (lifeCounter > 0) {
                        body.setPosition(newPosition);
                        body.setLinearVelocity({ 0, 0 }); // Reset the forces
                    }
                }
            }
        });
    }

    void LifeSystem::render(engine::IRenderer& /*renderer*/) {}
}
}
