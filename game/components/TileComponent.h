#pragma once

#include <engine/ecs/Component.h>

namespace game::components {
struct TileComponent : public engine::ecs::BaseComponent<TileComponent> {
};
}
