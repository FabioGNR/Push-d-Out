#pragma once

#include <engine/ecs/Component.h>
#include <engine/ecs/Entity.h>
#include <vector>

namespace game {
namespace components {
struct InventoryComponent : public engine::ecs::BaseComponent<InventoryComponent> {
    std::vector<engine::ecs::Entity> equipped;
};
}
}