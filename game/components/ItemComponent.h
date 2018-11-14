#pragma once

#include <game/definitions/ItemType.h>

#include <engine/ecs/Component.h>
#include <engine/physics/Body.h>

#include <chrono>

namespace game {
namespace components {
    struct ItemComponent : public engine::ecs::BaseComponent<ItemComponent> {
        definitions::ItemType type;

        ItemComponent(definitions::ItemType type)
            : type(type)
        {
        }
    };
}
}