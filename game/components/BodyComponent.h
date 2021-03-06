#pragma once

#include <engine/ecs/Component.h>
#include <engine/physics/Body.h>

namespace game {
namespace components {
    struct BodyComponent : public engine::ecs::BaseComponent<BodyComponent> {
        const engine::physics::Body* body;

        explicit BodyComponent(const engine::physics::Body* body)
            : body(body){};
    };
}
}
