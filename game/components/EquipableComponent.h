#pragma once

#include "game/components/EquipmentSpawnerComponent.h"
#include <engine/ecs/Component.h>
#include <vector>

namespace game {
namespace components {
    struct EquipableComponent : public engine::ecs::BaseComponent<EquipableComponent> {
        explicit EquipableComponent(EquipmentSpawnerComponent& spawner)
            : spawner(spawner)
        {
        }
        EquipmentSpawnerComponent& spawner;
    };
}
}