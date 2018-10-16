#pragma once

#include <ecs/Component.h>

namespace game {
    namespace components {
        struct ProjectileComponent : public engine::ecs::BaseComponent<ProjectileComponent> {

            ProjectileComponent(){};
        };
    }
}