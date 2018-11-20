#pragma once

#include <chrono>
#include <engine/ecs/Component.h>

namespace game {
namespace components {
    struct EquipmentSpawnerComponent : public engine::ecs::BaseComponent<EquipmentSpawnerComponent> {
        std::chrono::nanoseconds timeSinceSpawn{ 0 };
        bool hasEquipment{ false };
        double spawnIntervalSeconds;
        explicit EquipmentSpawnerComponent(double _spawnIntervalSeconds)
            : spawnIntervalSeconds{ _spawnIntervalSeconds }
        {
        }
    };
}
}