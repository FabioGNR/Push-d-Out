#pragma once

#include <engine/ecs/Component.h>

namespace game {
namespace components {
    struct DestructibleComponent : public engine::ecs::BaseComponent<DestructibleComponent> {
    };
}
}
