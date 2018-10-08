//
// Created by Joris on 8-10-2018.
//

#pragma once

#include <ecs/Component.h>

namespace game {
namespace components {
    struct CharacterSpawnComponent : public engine::BaseComponent<CharacterSpawnComponent> {

        CharacterSpawnComponent() {};
    };
}
}