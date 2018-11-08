#pragma once

#include <engine/ecs/Component.h>
#include <vector>

namespace game {
namespace components {
    struct EquipableComponent : public engine::ecs::BaseComponent<EquipableComponent> {
        EquipableComponent() = default;
    };
}
}