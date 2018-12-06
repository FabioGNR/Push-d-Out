#include "WeaponSystem.h"

#include <chrono>
#include <engine/graphics/IRenderer.h>
#include <engine/physics/Body.h>
#include <engine/physics/DynamicBody.h>
#include <game/builders/SpriteBuilder.h>
#include <game/components/BodyComponent.h>
#include <game/components/DimensionComponent.h>
#include <game/components/InventoryComponent.h>
#include <game/components/PlayerInputComponent.h>
#include <game/components/PositionComponent.h>
#include <game/components/ProjectileComponent.h>
#include <game/components/SpriteComponent.h>
#include <game/listeners/ProjectileContactListener.h>
#include <game/listeners/ProjectilePortalContactListener.h>
#include <memory>

using namespace game::components;
using namespace game::definitions;

engine::ecs::Entity& fireForceGun(const engine::ecs::Entity& entity,
    const common::Vector2D<double>& playerPosition,
    engine::physics::World& physicsWorld,
    engine::ecs::World& ecsWorld)
{
    common::Vector2D<double> projPos = playerPosition + common::Vector2D<double>(1.5, 1);
    auto& projectileEntity = ecsWorld.createEntity();
    common::Vector2D<double> dimensionVector(0.5, 0.5);

    auto posComponent = PositionComponent(playerPosition);
    ecsWorld.addComponent<PositionComponent>(projectileEntity, posComponent);

    auto projectileBody = physicsWorld.createDynamicBody(projPos, dimensionVector, projectileEntity.id());
    projectileBody->setLinearVelocity(common::Vector2D<double>(200, 0));
    projectileBody->setGravityScale(0);
    projectileBody->setBullet(true);
    ecsWorld.addComponent<BodyComponent>(projectileEntity, BodyComponent(std::move(projectileBody)));

    auto dimensionComponent = DimensionComponent(dimensionVector);
    ecsWorld.addComponent<DimensionComponent>(projectileEntity, dimensionComponent);

    auto projectileComponent = ProjectileComponent(game::definitions::WeaponType::ForceGun, game::definitions::ProjectileType::Force);
    ecsWorld.addComponent<ProjectileComponent>(projectileEntity, projectileComponent);
    ecsWorld.getComponent<BodyComponent>(entity).body->applyForce(common::Vector2D<double>(-600, 0), playerPosition);

    auto sprites = game::builders::SpriteBuilder{ "assets/sprites/projectiles/projectiles.png", "assets/sprites/projectiles/projectiles.json" }.build();
    auto sprite = sprites.find("ForceGunProjectile");
    if (sprite != sprites.end()) {
        ecsWorld.addComponent<SpriteComponent>(projectileEntity, sprite->second);
    }
    return projectileEntity;
}

engine::ecs::Entity& firePortalGun(const engine::ecs::Entity& /* entity */, const common::Vector2D<double> position,
    engine::physics::World& physicsWorld,
    engine::ecs::World& ecsWorld, bool alternative)
{
    // Create projectile
    auto& projectileEntity = ecsWorld.createEntity();
    common::Vector2D<double> dimensionVector(0.5, 0.5);

    auto projectileBody = physicsWorld.createDynamicBody(position + common::Vector2D(1.5, 1.0), dimensionVector, projectileEntity.id());
    projectileBody->setGravityScale(0.8);
    projectileBody->setLinearVelocity(common::Vector2D<double>(20, 0));
    ecsWorld.addComponent<BodyComponent>(projectileEntity, BodyComponent(std::move(projectileBody)));

    auto posComponent = PositionComponent(position);
    ecsWorld.addComponent<PositionComponent>(projectileEntity, posComponent);

    auto dimensionComponent = DimensionComponent(dimensionVector);
    ecsWorld.addComponent<DimensionComponent>(projectileEntity, dimensionComponent);

    auto projectileComponent = ProjectileComponent(WeaponType::PortalGun, alternative ? ProjectileType::OrangePortal : ProjectileType::BluePortal);
    ecsWorld.addComponent<ProjectileComponent>(projectileEntity, projectileComponent);

    auto spritePath = "assets/sprites/projectiles/projectiles.png";
    auto sprites = game::builders::SpriteBuilder{ spritePath, "assets/sprites/projectiles/projectiles.json" }.build();
    auto sprite = sprites.find(alternative ? "OrangePortalProjectile" : "BluePortalProjectile");
    if (sprite != sprites.end()) {
        ecsWorld.addComponent<SpriteComponent>(projectileEntity, sprite->second);
    }
    return projectileEntity;
}

engine::ecs::Entity& firePrimaryPortalGun(const engine::ecs::Entity& entity, const common::Vector2D<double> position,
    engine::physics::World& physicsWorld,
    engine::ecs::World& ecsWorld)
{
    return firePortalGun(entity, position, physicsWorld, ecsWorld, false);
}

engine::ecs::Entity& fireSecondaryPortalGun(const engine::ecs::Entity& entity, const common::Vector2D<double> position,
    engine::physics::World& physicsWorld,
    engine::ecs::World& ecsWorld)
{
    return firePortalGun(entity, position, physicsWorld, ecsWorld, true);
}

namespace game {
namespace systems {

    WeaponSystem::WeaponSystem(engine::ecs::World& ecsWorld, engine::physics::World& physicsWorld, engine::input::InputManager& inputManager)
        : m_ecsWorld(ecsWorld)
        , m_physicsWorld(physicsWorld)
        , m_inputMap(inputManager.getMap())
    {
        fireFunctionMap[definitions::WeaponType::ForceGun] = fireForceGun;
        fireFunctionMap[definitions::WeaponType::PortalGun] = firePrimaryPortalGun;

        altFireFunctionMap[definitions::WeaponType::PortalGun] = fireSecondaryPortalGun;

        m_physicsWorld.addContactListener(std::make_unique<game::listeners::ProjectileContactListener>(m_ecsWorld, m_physicsWorld));
        m_physicsWorld.addContactListener(std::make_unique<game::listeners::ProjectilePortalContactListener>(m_ecsWorld));
        m_physicsWorld.addContactListener(std::make_unique<game::listeners::PortalContactListener>(m_ecsWorld));
    }

    void WeaponSystem::update(std::chrono::nanoseconds timeStep)
    {
        // increment all the timeSinceLastFired for weapons
        m_ecsWorld.forEachEntityWith<WeaponComponent>([&](engine::ecs::Entity& entity) {
            auto& weapon = m_ecsWorld.getComponent<components::WeaponComponent>(entity);
            if (weapon.wasPrimaryFired) {
                weapon.timeSinceLastPrimaryFired += timeStep;
            }
            if (weapon.hasSecondaryFire && weapon.wasSecondaryFired) {
                weapon.timeSinceLastSecondaryFired += timeStep;
            }
        });

        // check if players want to fire a weapon
        m_ecsWorld.forEachEntityWith<PlayerInputComponent, InventoryComponent, PositionComponent>([&](engine::ecs::Entity& entity) {
            auto& inventory = m_ecsWorld.getComponent<InventoryComponent>(entity);
            auto& inputComponent = m_ecsWorld.getComponent<PlayerInputComponent>(entity);
            if (inventory.activeEquipment.hasValue()) {
                engine::ecs::Entity weaponEntity = inventory.activeEquipment.get();
                auto& weapon = m_ecsWorld.getComponent<components::WeaponComponent>(weaponEntity);
                auto& analogMap = m_inputMap.getMap(inputComponent.controllerId);

                // primary fire
                const auto primaryAction = definitions::Action::UseWeapon;
                const auto control = inputComponent.getKey(primaryAction);
                const auto analogControl = inputComponent.getAnalog(primaryAction);

                if (analogMap.getValue(analogControl) > 1) {
                    fire(entity, weapon);
                }

                if (analogMap.hasKeyState(control, engine::input::KeyStates::DOWN)) {
                    fire(entity, weapon);
                }

                if (!weapon.hasSecondaryFire) {
                    return;
                }

                // alt fire
                const auto secondaryActions = definitions::Action::UseWeaponAlternative;
                const auto secondaryControl = inputComponent.getKey(secondaryActions);
                const auto secondaryAnalogControl = inputComponent.getAnalog(secondaryActions);

                if (analogMap.getValue(secondaryAnalogControl) > 1) {
                    altFire(entity, weapon);
                }

                if (analogMap.hasKeyState(secondaryControl, engine::input::KeyStates::DOWN)) {
                    altFire(entity, weapon);
                }
            }
        });
    }

    void WeaponSystem::fire(engine::ecs::Entity& entity, game::components::WeaponComponent& weapon)
    {
        using milliseconds = std::chrono::milliseconds;
        double secondsSinceFired = std::chrono::duration_cast<milliseconds>(weapon.timeSinceLastPrimaryFired).count() / 1000.0;
        if (!weapon.wasPrimaryFired || secondsSinceFired > weapon.primaryCooldown) {
            if (fireFunctionMap.find(weapon.type) != fireFunctionMap.end()) {
                auto& position = m_ecsWorld.getComponent<PositionComponent>(entity);
                fireFunctionMap[weapon.type](entity, position.position, m_physicsWorld, m_ecsWorld);
                weapon.timeSinceLastPrimaryFired = std::chrono::nanoseconds(0);
                weapon.wasPrimaryFired = true;
            }
        }
    }

    void WeaponSystem::altFire(engine::ecs::Entity& entity, game::components::WeaponComponent& weapon)
    {
        if (!weapon.hasSecondaryFire) {
            return;
        }

        using milliseconds = std::chrono::milliseconds;
        double secondsSinceFired = std::chrono::duration_cast<milliseconds>(weapon.timeSinceLastSecondaryFired).count() / 1000.0;
        if (!weapon.wasSecondaryFired || secondsSinceFired > weapon.secondaryCooldown) {
            if (fireFunctionMap.find(weapon.type) != fireFunctionMap.end()) {
                auto& position = m_ecsWorld.getComponent<PositionComponent>(entity);
                altFireFunctionMap[weapon.type](entity, position.position, m_physicsWorld, m_ecsWorld);
                weapon.timeSinceLastSecondaryFired = std::chrono::nanoseconds(0);
                weapon.wasSecondaryFired = true;
            }
        }
    }

    void WeaponSystem::render(engine::IRenderer& /* renderer */) {}
}
}
