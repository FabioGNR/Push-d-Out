#pragma once

#include <ecs/Component.h>
#include <physics/Body.h>
#include "game/definitions/WeaponType.h"
#include <chrono>

namespace game {
namespace components {
    struct WeaponComponent : public engine::ecs::BaseComponent<WeaponComponent> {
        double cooldownSeconds;
        definitions::WeaponType type;
        std::chrono::time_point<std::chrono::steady_clock> lastFired;

        WeaponComponent(double cooldownSeconds, definitions::WeaponType type)
            : cooldownSeconds(cooldownSeconds)
            , type(type)
            , lastFired(){};
    };
}
}