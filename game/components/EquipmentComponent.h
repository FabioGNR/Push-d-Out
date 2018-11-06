#pragma once

#include <engine/ecs/Component.h>

namespace game {
namespace components {
    struct EquipmentComponent : public engine::ecs::BaseComponent<EquipmentComponent> {
        double weight;
        explicit EquipmentComponent(double weight)
            : weight(weight){};
    };
}
}