#include "WeaponSystem.h"

#include <game/builders/SpriteBuilder.h>
#include <game/components/BodyComponent.h>
#include <game/components/DimensionComponent.h>
#include <game/components/InventoryComponent.h>
#include <game/components/PlayerInputComponent.h>
#include <game/components/PositionComponent.h>
#include <game/components/ProjectileComponent.h>

#include <engine/graphics/IRenderer.h>
#include <engine/physics/Body.h>
#include <engine/physics/DynamicBody.h>

#include <chrono>
#include <game/components/SpriteComponent.h>

using namespace game::components;

engine::ecs::Entity& fireForceGun(const engine::ecs::Entity& entity,
    const common::Vector2D<double>& playerPosition,
    engine::physics::World& physicsWorld,
    engine::ecs::World& ecsWorld)
{
    common::Vector2D<double> projPos = playerPosition + common::Vector2D<double>(1, 1);
    auto& projectileEntity = ecsWorld.createEntity();
    common::Vector2D<double> dimensionVector(0.5, 0.5);
    engine::physics::Body* projectileBody = physicsWorld.createKinematicBody(projPos, dimensionVector, projectileEntity.id());

    auto posComponent = PositionComponent(playerPosition);
    ecsWorld.addComponent<PositionComponent>(projectileEntity, posComponent);

    auto bodyComponent = BodyComponent(projectileBody);
    ecsWorld.addComponent<BodyComponent>(projectileEntity, bodyComponent);

    auto dimensionComponent = DimensionComponent(dimensionVector);
    ecsWorld.addComponent<DimensionComponent>(projectileEntity, dimensionComponent);

    auto projectileComponent = ProjectileComponent();
    ecsWorld.addComponent<ProjectileComponent>(projectileEntity, projectileComponent);
    projectileBody->setLinearVelocity(common::Vector2D<double>(20, 0));
    ecsWorld.getComponent<BodyComponent>(entity).body->applyForce(common::Vector2D<double>(-600, 0), playerPosition);

    auto sprites = game::builders::SpriteBuilder{ "assets/sprites/misc/ForceGunProjectile.png", "assets/sprites/misc/datafile.json" }.build();
    auto sprite = sprites.find("ForceGunProjectile");
    if (sprite != sprites.end()) {
        ecsWorld.addComponent<SpriteComponent>(projectileEntity, sprite->second);
    }
    return projectileEntity;
}

namespace game {
namespace systems {

    WeaponSystem::WeaponSystem(engine::ecs::World& ecsWorld, engine::physics::World& physicsWorld, engine::input::InputManager& inputManager)
        : m_ecsWorld(ecsWorld)
        , m_physicsWorld(physicsWorld)
        , m_inputMap(inputManager.getMap())
    {
        fireFunctionMap[definitions::WeaponType::ForceGun] = fireForceGun;
    }

    void WeaponSystem::update(std::chrono::nanoseconds timeStep)
    {

        // increment all the timeSinceLastFired for weapons
        m_ecsWorld.forEachEntityWith<WeaponComponent>([&](engine::ecs::Entity& entity) {
            auto& weapon = m_ecsWorld.getComponent<components::WeaponComponent>(entity);
            if (weapon.wasFired) {
                weapon.timeSinceLastFired += timeStep;
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
                const auto action = definitions::Action::UseWeapon;
                const auto control = inputComponent.getKey(action);
                const auto analogControl = inputComponent.getAnalog(action);

                if (analogMap.getValue(analogControl) > 1) {
                    shoot(entity, weapon);
                }

                if (analogMap.hasKeyState(control, engine::input::KeyStates::DOWN)) {
                    shoot(entity, weapon);
                }
            }
        });
    }

    void WeaponSystem::shoot(engine::ecs::Entity& entity, game::components::WeaponComponent& weapon)
    {
        using milliseconds = std::chrono::milliseconds;
        double secondsSinceFired = std::chrono::duration_cast<milliseconds>(weapon.timeSinceLastFired).count() / 1000.0;
        if (!weapon.wasFired || secondsSinceFired > weapon.cooldownSeconds) {
            if (fireFunctionMap.find(weapon.type) != fireFunctionMap.end()) {
                auto& position = m_ecsWorld.getComponent<PositionComponent>(entity);
                fireFunctionMap[weapon.type](entity, position.position, m_physicsWorld, m_ecsWorld);
                weapon.timeSinceLastFired = std::chrono::nanoseconds(0);
                weapon.wasFired = true;
            }
        }
    }

    void WeaponSystem::render(engine::IRenderer& /* renderer */) {}
}
}
