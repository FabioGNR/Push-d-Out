#pragma once

#include <ecs/Component.h>

namespace game {
    namespace components {
        struct EquipmentComponent : public engine::ecs::BaseComponent<EquipmentComponent> {

            EquipmentComponent() {};
        };
    }
}