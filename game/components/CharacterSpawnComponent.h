#pragma once

#include <engine/ecs/Component.h>

namespace game {
namespace components {
    struct CharacterSpawnComponent : public engine::ecs::BaseComponent<CharacterSpawnComponent> {
        CharacterSpawnComponent() = default;
    };
}
}