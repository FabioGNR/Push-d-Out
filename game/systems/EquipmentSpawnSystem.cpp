#include "EquipmentSpawnSystem.h"
#include "game/components/EquipmentSpawnerComponent.h"
#include "game/components/PositionComponent.h"
#include <game/components/EquipableComponent.h>
namespace game {
using namespace components;
namespace systems {

    void EquipmentSpawnSystem::update(std::chrono::nanoseconds timeStep)
    {
        using milliseconds = std::chrono::milliseconds;
        m_world.forEachEntityWith<EquipmentSpawnerComponent, PositionComponent>([&](engine::ecs::Entity& entity) {
            auto& spawnerComponent = m_world.getComponent<EquipmentSpawnerComponent>(entity);
            if (!spawnerComponent.hasEquipment) {
                spawnerComponent.timeSinceSpawn += timeStep;
                double secondsSinceSpawn = std::chrono::duration_cast<milliseconds>(spawnerComponent.timeSinceSpawn).count() / 1000.0;
                if (secondsSinceSpawn > spawnerComponent.spawnIntervalSeconds) {
                    spawnerComponent.timeSinceSpawn = std::chrono::nanoseconds(0);
                    spawnerComponent.hasEquipment = true;
                    auto& positionComponent = m_world.getComponent<PositionComponent>(entity);
                    auto spawnPosition = positionComponent.position;
                    spawnPosition += m_spawnOffset;
                    // create the equipment in the world and link the spawner
                    engine::ecs::Entity& equipment = m_equipmentFactory.createRandomEquipment(spawnPosition);
                    components::EquipableComponent equipable{ spawnerComponent };
                    m_world.addComponent<components::EquipableComponent>(equipment, equipable);
                }
            }
        });
    }

    void EquipmentSpawnSystem::render(engine::IRenderer& /*renderer*/)
    {
    }
}
}