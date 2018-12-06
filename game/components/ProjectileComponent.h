#pragma once

#include <engine/ecs/Component.h>
#include <game/definitions/ProjectileType.h>
#include <game/definitions/WeaponType.h>

namespace game {
namespace components {
    struct ProjectileComponent : public engine::ecs::BaseComponent<ProjectileComponent> {
        game::definitions::WeaponType weaponType;
        game::definitions::ProjectileType type;

        ProjectileComponent(game::definitions::WeaponType weaponType, game::definitions::ProjectileType type)
            : weaponType{ weaponType }
            , type{ type } {};
    };
}
}