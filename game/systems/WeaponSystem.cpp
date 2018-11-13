#include "WeaponSystem.h"

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

using namespace game::components;

engine::ecs::Entity& fireForceGun(const engine::ecs::Entity& entity,
    const common::Vector2D<double>& playerPosition,
    engine::physics::World& physicsWorld,
    engine::ecs::World& ecsWorld)
{
    common::Vector2D<double> projPos = playerPosition + common::Vector2D<double>(1, 1);
    auto& projectileEntity = ecsWorld.createEntity();
    common::Vector2D<double> dimensionVector(0.5, 0.5);
    const engine::physics::Body* projectileBody = physicsWorld.createKinematicBody(projPos, dimensionVector);

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

    return projectileEntity;
}

namespace game {
namespace systems {

    WeaponSystem::WeaponSystem(engine::ecs::World& ecsWorld, engine::physics::World& physicsWorld, engine::input::InputManager& inputManager)
        : m_ecsWorld(ecsWorld)
        , m_physicsWorld(physicsWorld)
    {
        fireFunctionMap[definitions::WeaponType::ForceGun] = fireForceGun;
        std::cout << "After inserting in to map" << std::endl;

        m_inputSubscription = inputManager.subscribe([&](engine::input::maps::AnalogMap analogMap, engine::events::Subscription<engine::input::maps::AnalogMap>&) {
            m_analogMap = analogMap;
        },
            1);
    }

    void game::systems::WeaponSystem::update(std::chrono::nanoseconds /* timeStep */)
    {

        m_ecsWorld.forEachEntityWith<PlayerInputComponent, InventoryComponent, PositionComponent>([&](engine::ecs::Entity& entity) {
            auto& inventory = m_ecsWorld.getComponent<InventoryComponent>(entity);
            auto& inputComponent = m_ecsWorld.getComponent<PlayerInputComponent>(entity);
            if (inventory.activeEquipment.hasValue()) {
                engine::ecs::Entity weaponEntity = inventory.activeEquipment.get();
                auto& weapon = m_ecsWorld.getComponent<components::WeaponComponent>(weaponEntity);
                auto action = definitions::Action::UseWeapon;
                auto control = inputComponent.getKey(action);
                auto analogControl = inputComponent.getAnalog(action);

                if (m_analogMap.getValue(analogControl) > 1) {
                    shoot(entity, weapon);
                }

                if (m_analogMap.hasKeyState(control, engine::input::KeyStates::DOWN)) {
                    shoot(entity, weapon);
                }
            }
        });
    }

    void game::systems::WeaponSystem::shoot(engine::ecs::Entity& entity, game::components::WeaponComponent& weapon)
    {
        using clock = std::chrono::steady_clock;
        if (std::chrono::duration_cast<std::chrono::milliseconds>(clock::now() - weapon.lastFired).count() > weapon.cooldownSeconds * 1000) {
            if (fireFunctionMap.find(weapon.type) != fireFunctionMap.end()) {
                auto& position = m_ecsWorld.getComponent<PositionComponent>(entity);
                fireFunctionMap[weapon.type](entity, position.position, m_physicsWorld, m_ecsWorld);
                weapon.lastFired = clock::now();
            }
        }
    }

    void game::systems::WeaponSystem::render(engine::IRenderer& /* renderer */) {}
}
}
