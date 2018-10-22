#pragma once

#include <ecs/Component.h>
#include <physics/Body.h>
#include "game/definitions/WeaponType.h"

namespace game {
namespace components {
    struct WeaponComponent : public engine::ecs::BaseComponent<WeaponComponent> {
        double cooldownSeconds;
        definitions::WeaponType type;

        WeaponComponent(double cooldownSeconds, definitions::WeaponType type)
            : cooldownSeconds(cooldownSeconds)
            , type(type){};
    };
}
}