#pragma once

#include "game/equipment/InventorySlot.h"
#include <engine/ecs/Component.h>
#include <engine/ecs/Entity.h>
#include <vector>

namespace game {
namespace components {
    struct InventoryComponent : public engine::ecs::BaseComponent<InventoryComponent> {
        equipment::InventorySlot activeEquipment;
        equipment::InventorySlot otherEquipment;
        equipment::InventorySlot item;
    };
}
}