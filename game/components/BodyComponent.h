#pragma once

#include <engine/ecs/Component.h>
#include <engine/physics/Body.h>

namespace game {
namespace components {
    struct BodyComponent : public engine::ecs::BaseComponent<BodyComponent> {
        std::unique_ptr<engine::physics::Body> body;

        explicit BodyComponent(std::unique_ptr<engine::physics::Body> body)
            : body(std::move(body)){};
    };
}
}
