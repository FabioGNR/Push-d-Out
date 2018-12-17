#include "WeaponSystem.h"

#include "engine/input/maps/InputMap.h"
#include <chrono>
#include <engine/graphics/IRenderer.h>
#include <engine/physics/Body.h>
#include <engine/physics/DynamicBody.h>
#include <game/builders/SpriteBuilder.h>
#include <game/components/BodyComponent.h>
#include <game/components/DimensionComponent.h>
#include <game/components/InventoryComponent.h>
#include <game/components/OnOutOfBoundsDeleteComponent.h>
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
    engine::physics::World* physicsWorld,
    engine::ecs::World* ecsWorld,
    common::Vector2D<double>& direction)
{
    auto playerDimension = ecsWorld->getComponent<DimensionComponent>(entity).dimension;
    common::Vector2D<double> dimensionVector(0.5, 0.5);
    common::Vector2D<double> shootDirection = direction;
    shootDirection *= playerDimension / 2 + dimensionVector;
    common::Vector2D<double> projPos = playerPosition + playerDimension / 2 + (shootDirection * 1.5);

    auto& projectileEntity = ecsWorld->createEntity();
    auto posComponent = PositionComponent(playerPosition);
    ecsWorld->addComponent<PositionComponent>(projectileEntity, posComponent);

    auto projectileBody = physicsWorld->createDynamicBody(projPos, dimensionVector, projectileEntity.id());
    projectileBody->setLinearVelocity(direction * 20);
    projectileBody->setDensity(2);
    projectileBody->setGravityScale(0);
    projectileBody->setBullet(true);
    ecsWorld->addComponent<BodyComponent>(projectileEntity, BodyComponent(std::move(projectileBody)));

    auto dimensionComponent = DimensionComponent(dimensionVector);
    ecsWorld->addComponent<DimensionComponent>(projectileEntity, dimensionComponent);

    auto projectileComponent = ProjectileComponent(game::definitions::WeaponType::ForceGun, game::definitions::ProjectileType::Force);
    projectileComponent.force = direction;
    ecsWorld->addComponent<ProjectileComponent>(projectileEntity, projectileComponent);
    ecsWorld->addComponent<OnOutOfBoundsDeleteComponent>(projectileEntity);
    ecsWorld->getComponent<BodyComponent>(entity).body->applyForce(common::Vector2D<double>((direction.x > 0 ? -600 : 600), 0), playerPosition);

    auto sprites = game::builders::SpriteBuilder{ "assets/sprites/projectiles/projectiles.png", "assets/sprites/projectiles/projectiles.json" }.build();
    auto sprite = sprites.find("ForceGunProjectile");
    if (sprite != sprites.end()) {
        ecsWorld->addComponent<SpriteComponent>(projectileEntity, sprite->second);
    }
    return projectileEntity;
}

engine::ecs::Entity& firePortalGun(const engine::ecs::Entity& entity, const common::Vector2D<double> position,
    engine::physics::World* physicsWorld,
    engine::ecs::World* ecsWorld,
    common::Vector2D<double>& direction,
    bool alternative)
{
    auto playerDimension = ecsWorld->getComponent<DimensionComponent>(entity).dimension;
    common::Vector2D<double> dimensionVector(0.5, 0.5);
    common::Vector2D<double> shootDirection = direction;
    shootDirection *= playerDimension / 2 + dimensionVector;
    common::Vector2D<double> projPos = position + playerDimension / 2 + (shootDirection * 1.5);

    // Create projectile
    auto& projectileEntity = ecsWorld->createEntity();

    auto projectileBody = physicsWorld->createDynamicBody(projPos, dimensionVector, projectileEntity.id());
    projectileBody->setGravityScale(0.8);
    projectileBody->setLinearVelocity(direction * 20);
    ecsWorld->addComponent<BodyComponent>(projectileEntity, BodyComponent(std::move(projectileBody)));

    auto posComponent = PositionComponent(projPos);
    ecsWorld->addComponent<PositionComponent>(projectileEntity, posComponent);

    auto dimensionComponent = DimensionComponent(dimensionVector);
    ecsWorld->addComponent<DimensionComponent>(projectileEntity, dimensionComponent);

    auto projectileComponent = ProjectileComponent(WeaponType::PortalGun, alternative ? ProjectileType::OrangePortal : ProjectileType::BluePortal);
    ecsWorld->addComponent<ProjectileComponent>(projectileEntity, projectileComponent);
    ecsWorld->addComponent<OnOutOfBoundsDeleteComponent>(projectileEntity);

    auto spritePath = "assets/sprites/projectiles/projectiles.png";
    auto sprites = game::builders::SpriteBuilder{ spritePath, "assets/sprites/projectiles/projectiles.json" }.build();
    auto sprite = sprites.find(alternative ? "OrangePortalProjectile" : "BluePortalProjectile");
    if (sprite != sprites.end()) {
        ecsWorld->addComponent<SpriteComponent>(projectileEntity, sprite->second);
    }
    return projectileEntity;
}

engine::ecs::Entity& firePrimaryPortalGun(const engine::ecs::Entity& entity, const common::Vector2D<double> position,
    engine::physics::World* physicsWorld,
    engine::ecs::World* ecsWorld,
    common::Vector2D<double>& direction)
{
    return firePortalGun(entity, position, physicsWorld, ecsWorld, direction, false);
}

engine::ecs::Entity& fireSecondaryPortalGun(const engine::ecs::Entity& entity, const common::Vector2D<double> position,
    engine::physics::World* physicsWorld,
    engine::ecs::World* ecsWorld,
    common::Vector2D<double>& direction)
{
    return firePortalGun(entity, position, physicsWorld, ecsWorld, direction, true);
}

namespace game {
namespace systems {

    WeaponSystem::WeaponSystem(engine::ecs::World* ecsWorld, engine::physics::World* physicsWorld, engine::input::InputManager* inputManager, engine::graphics::Camera* camera)
        : m_ecsWorld(ecsWorld)
        , m_physicsWorld(physicsWorld)
        , m_camera(camera)
        , m_inputMaps(inputManager->getMap())
    {
        fireFunctionMap[definitions::WeaponType::ForceGun] = fireForceGun;
        fireFunctionMap[definitions::WeaponType::PortalGun] = firePrimaryPortalGun;

        altFireFunctionMap[definitions::WeaponType::PortalGun] = fireSecondaryPortalGun;

        m_physicsWorld->addContactListener(std::make_unique<game::listeners::ProjectileContactListener>(m_ecsWorld, m_physicsWorld));
        m_physicsWorld->addContactListener(std::make_unique<game::listeners::ProjectilePortalContactListener>(m_ecsWorld));
        m_physicsWorld->addContactListener(std::make_unique<game::listeners::PortalContactListener>(m_ecsWorld));
    }

    void WeaponSystem::update(std::chrono::nanoseconds timeStep)
    {
        // increment all the timeSinceLastFired for weapons
        m_ecsWorld->forEachEntityWith<WeaponComponent>([&](engine::ecs::Entity& entity) {
            auto& weapon = m_ecsWorld->getComponent<components::WeaponComponent>(entity);
            if (weapon.wasPrimaryFired) {
                weapon.timeSinceLastPrimaryFired += timeStep;
            }
            if (weapon.hasSecondaryFire && weapon.wasSecondaryFired) {
                weapon.timeSinceLastSecondaryFired += timeStep;
            }
        });

        // check if players want to fire a weapon
        m_ecsWorld->forEachEntityWith<PlayerInputComponent, InventoryComponent, PositionComponent>([&](engine::ecs::Entity& entity) {
            const auto& inventory = m_ecsWorld->getComponent<InventoryComponent>(entity);
            const auto& inputComponent = m_ecsWorld->getComponent<PlayerInputComponent>(entity);
            const auto& directionComponent = m_ecsWorld->getComponent<DirectionComponent>(entity);
            const auto positionComponent = m_ecsWorld->getComponent<PositionComponent>(entity);

            if (inventory.activeEquipment.hasValue()) {
                const engine::ecs::Entity weaponEntity = *inventory.activeEquipment.get();
                auto& weapon = m_ecsWorld->getComponent<components::WeaponComponent>(weaponEntity);

                auto& test = m_ecsWorld->getComponent<PositionComponent>(weaponEntity);
                test = positionComponent;

                const auto& inputMap = m_inputMaps->getMap(inputComponent.controllerId);
                const auto action = definitions::Action::UseWeapon;
                const auto control = inputComponent.getKey(action);
                const auto analogControl = inputComponent.getAnalog(action);

                // primary fire
                if (inputMap.getValue(analogControl) > 1) {
                    auto analogDirection = common::Vector2D<int>(inputMap.getValue(engine::input::AnalogKeys::CON_RIGHTSTICK_X), inputMap.getValue(engine::input::AnalogKeys::CON_RIGHTSTICK_Y));
                    shoot(entity, weapon, calculateDirection(entity, analogDirection, directionComponent));
                } else if (inputMap.hasState(control, engine::input::States::DOWN)) {
                    auto mousePosition = common::Vector2D<int>(inputMap.getValue(engine::input::AnalogKeys::MOUSE_X), inputMap.getValue(engine::input::AnalogKeys::MOUSE_Y));
                    shoot(entity, weapon, calculateDirection(entity, mousePosition, directionComponent));
                }

                if (!weapon.hasSecondaryFire) {
                    return; // nothing to do further
                }

                const auto secondaryAction = definitions::Action::UseWeaponAlternative;
                const auto secondaryControl = inputComponent.getKey(secondaryAction);
                const auto secondaryAnalogControl = inputComponent.getAnalog(secondaryAction);

                // alt fire
                if (inputMap.getValue(secondaryAnalogControl) > 1) {
                    auto analogDirection = common::Vector2D<int>(inputMap.getValue(engine::input::AnalogKeys::CON_RIGHTSTICK_X), inputMap.getValue(engine::input::AnalogKeys::CON_RIGHTSTICK_Y));
                    shootAlternative(entity, weapon, calculateDirection(entity, analogDirection, directionComponent));
                } else if (inputMap.hasState(secondaryControl, engine::input::States::DOWN)) {
                    auto mousePosition = common::Vector2D<int>(inputMap.getValue(engine::input::AnalogKeys::MOUSE_X), inputMap.getValue(engine::input::AnalogKeys::MOUSE_Y));
                    shootAlternative(entity, weapon, calculateDirection(entity, mousePosition, directionComponent));
                }
            }
        });
    }

    void WeaponSystem::shoot(const engine::ecs::Entity& entity, game::components::WeaponComponent& weapon, common::Vector2D<double> fireDirection)
    {
        using milliseconds = std::chrono::milliseconds;
        const double
            secondsSinceFired
            = std::chrono::duration_cast<milliseconds>(weapon.timeSinceLastPrimaryFired).count() / 1000.0;
        if (!weapon.wasPrimaryFired || secondsSinceFired > weapon.primaryCooldown) {
            if (fireFunctionMap.find(weapon.type) != fireFunctionMap.end()) {
                const auto& position = m_ecsWorld->getComponent<PositionComponent>(entity);
                fireFunctionMap[weapon.type](entity, position.position, m_physicsWorld, m_ecsWorld, fireDirection);
                weapon.timeSinceLastPrimaryFired = std::chrono::nanoseconds(0);
                weapon.wasPrimaryFired = true;
            }
        }
    }

    void WeaponSystem::shootAlternative(engine::ecs::Entity& entity, game::components::WeaponComponent& weapon, common::Vector2D<double> fireDirection)
    {
        if (!weapon.hasSecondaryFire) {
            return;
        }

        using milliseconds = std::chrono::milliseconds;
        double secondsSinceFired = std::chrono::duration_cast<milliseconds>(weapon.timeSinceLastSecondaryFired).count() / 1000.0;
        if (!weapon.wasSecondaryFired || secondsSinceFired > weapon.secondaryCooldown) {
            if (fireFunctionMap.find(weapon.type) != fireFunctionMap.end()) {
                auto& position = m_ecsWorld->getComponent<PositionComponent>(entity);
                altFireFunctionMap[weapon.type](entity, position.position, m_physicsWorld, m_ecsWorld, fireDirection);
                weapon.timeSinceLastSecondaryFired = std::chrono::nanoseconds(0);
                weapon.wasSecondaryFired = true;
            }
        }
    }

    common::Vector2D<double> WeaponSystem::calculateDirection(const engine::ecs::Entity& entity, common::Vector2D<int>& direction, const game::components::DirectionComponent& directionComponent)
    {
        if (direction.x == 0 && direction.y == 0) {
            return common::Vector2D<double>((directionComponent.direction == DirectionComponent::Direction::RIGHT ? 1 : -1), 0);
        }

        auto playerPosition = m_camera->translatePosition(m_ecsWorld->getComponent<PositionComponent>(entity).position);

        direction.x -= playerPosition.x;
        direction.y -= playerPosition.y;

        auto normalizedDirection = direction.normalize();
        normalizedDirection.y = -normalizedDirection.y;

        return normalizedDirection;
    }

    void WeaponSystem::render(engine::IRenderer& /* renderer */) {}
}
}
