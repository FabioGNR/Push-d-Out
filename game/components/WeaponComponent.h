#pragma once

#include <ecs/Component.h>
#include <physics/Body.h>
#include "game/definitions/WeaponType.h"

namespace game {
namespace components {
    struct WeaponComponent : public engine::ecs::BaseComponent<WeaponComponent> {
        double cooldownSeconds;
        double weight;
        definitions::WeaponType type;

        WeaponComponent(double cooldownSeconds, double weight, definitions::WeaponType type)
            : cooldownSeconds(cooldownSeconds)
            , weight(weight)
            , type(type){};
    };
}
}