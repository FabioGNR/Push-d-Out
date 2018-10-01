#pragma once

#include "game/definitions/Body.h"
#include <engine/ecs/Component.h>

namespace game {
namespace components {
    struct BodyComponent : public engine::BaseComponent<BodyComponent> {
        definitions::Body body;

        BodyComponent(definitions::Body body)
            : body(body) {};
    };
}
}
