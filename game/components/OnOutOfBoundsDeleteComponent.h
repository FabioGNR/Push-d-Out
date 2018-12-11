#pragma once

#include <engine/common/Vector2D.h>
#include <engine/ecs/Component.h>

namespace game {
namespace components {
    struct OnOutOfBoundsDeleteComponent : public engine::ecs::BaseComponent<OnOutOfBoundsDeleteComponent> {
    };
}
}
