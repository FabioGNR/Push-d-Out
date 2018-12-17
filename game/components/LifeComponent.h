#pragma once

#include <engine/ecs/Component.h>

namespace game {
namespace components {
    struct LifeComponent : public engine::ecs::BaseComponent<LifeComponent> {
        int count;
        const int maximum;
        explicit LifeComponent(int count = 3)
            : count{ count }
            , maximum{ count }
        {
        }
    };
}
}