#pragma once

#include <engine/ecs/Component.h>
#include <game/definitions/ProjectileType.h>
#include <game/definitions/WeaponType.h>
#include "engine/common/Vector2D.h"

namespace game {
namespace components {
    struct ProjectileComponent : public engine::ecs::BaseComponent<ProjectileComponent> {
        game::definitions::WeaponType weaponType;
        game::definitions::ProjectileType type;

        common::Vector2D<double> force{};

        ProjectileComponent(game::definitions::WeaponType weaponType, game::definitions::ProjectileType type)
            : weaponType{ weaponType }
            , type{ type } {};
    };
}
}