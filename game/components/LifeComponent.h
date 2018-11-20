#pragma once

#include <engine/ecs/Component.h>

namespace game {
namespace components {
    struct LifeComponent : public engine::ecs::BaseComponent<LifeComponent> {
        int count;
        explicit LifeComponent(int count = 3)
            : count{ count }
        {
        }
    };
}
}