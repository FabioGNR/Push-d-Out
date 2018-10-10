#pragma once

#include "game/definitions/Body.h"
#include <engine/ecs/Component.h>
#include <engine/physics/Body.h>

namespace game {
namespace components {
    struct BodyComponent : public engine::ecs::BaseComponent<BodyComponent> {
        const engine::physics::Body* body;

        BodyComponent(const engine::physics::Body* body)
            : body(body){};
    };
}
}
