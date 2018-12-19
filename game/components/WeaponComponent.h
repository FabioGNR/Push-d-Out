#pragma once

#include <game/definitions/WeaponType.h>

#include <engine/ecs/Component.h>
#include <engine/physics/Body.h>

#include <chrono>
#include <game/definitions/ProjectileType.h>

namespace game {
namespace components {
    struct WeaponComponent : public engine::ecs::BaseComponent<WeaponComponent> {
        definitions::WeaponType type;

        double primaryCooldown = 0;
        std::chrono::nanoseconds timeSinceLastPrimaryFired{ 0 };
        bool wasPrimaryFired = false;
        definitions::ProjectileType primaryProjectile;

        bool hasSecondaryFire = false;
        double secondaryCooldown = 0;
        std::chrono::nanoseconds timeSinceLastSecondaryFired{ 0 };
        bool wasSecondaryFired = false;
        definitions::ProjectileType secondaryProjectile = definitions::ProjectileType::None;

        WeaponComponent(definitions::WeaponType type, double primaryCooldown, definitions::ProjectileType projectileType)
            : type(type)
            , primaryCooldown(primaryCooldown)
            , primaryProjectile(projectileType)
        {
        }

        WeaponComponent(definitions::WeaponType type, double primaryCooldown,
            definitions::ProjectileType primaryProjectileType,
            double secondaryCooldown, definitions::ProjectileType secondaryProjectileType)
            : type(type)
            , primaryCooldown(primaryCooldown)
            , primaryProjectile(primaryProjectileType)
            , secondaryCooldown(secondaryCooldown)
            , secondaryProjectile(secondaryProjectileType)
        {
            hasSecondaryFire = true;
        }
    };
}
}