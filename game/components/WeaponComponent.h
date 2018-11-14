#pragma once

#include <game/definitions/WeaponType.h>

#include <engine/ecs/Component.h>
#include <engine/physics/Body.h>

#include <chrono>

namespace game {
namespace components {
    struct WeaponComponent : public engine::ecs::BaseComponent<WeaponComponent> {
        double cooldownSeconds;
        definitions::WeaponType type;
        std::chrono::nanoseconds timeSinceLastFired{ 0 };
        bool wasFired = false;

        WeaponComponent(double cooldownSeconds, definitions::WeaponType type)
            : cooldownSeconds(cooldownSeconds)
            , type(type)
        {
        }
    };
}
}