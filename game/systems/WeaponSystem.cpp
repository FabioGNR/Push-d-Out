#include "WeaponSystem.h"

#include <game/components/BodyComponent.h>
#include <game/components/DimensionComponent.h>
#include <game/components/InventoryComponent.h>
#include <game/components/PlayerInputComponent.h>
#include <game/components/PositionComponent.h>
#include <game/components/ProjectileComponent.h>

#include "engine/input/maps/InputMap.h"
#include <engine/graphics/IRenderer.h>
#include <engine/physics/Body.h>
#include <engine/physics/DynamicBody.h>

#include <chrono>

using namespace game::components;

engine::ecs::Entity& fireForceGun(const engine::ecs::Entity& entity,
    const common::Vector2D<double>& playerPosition,
    engine::physics::World& physicsWorld,
    engine::ecs::World& ecsWorld,
    common::Vector2D<double>& direction)
{
    common::Vector2D<double> projPos = playerPosition + common::Vector2D<double>(1, 1);
    auto& projectileEntity = ecsWorld.createEntity();
    common::Vector2D<double> dimensionVector(0.5, 0.5);
    engine::physics::Body* projectileBody = physicsWorld.createKinematicBody(projPos, dimensionVector);

    auto posComponent = PositionComponent(playerPosition);
    ecsWorld.addComponent<PositionComponent>(projectileEntity, posComponent);

    auto bodyComponent = BodyComponent(projectileBody);
    ecsWorld.addComponent<BodyComponent>(projectileEntity, bodyComponent);

    auto dimensionComponent = DimensionComponent(dimensionVector);
    ecsWorld.addComponent<DimensionComponent>(projectileEntity, dimensionComponent);

    auto projectileComponent = ProjectileComponent();
    ecsWorld.addComponent<ProjectileComponent>(projectileEntity, projectileComponent);

    projectileBody->setLinearVelocity(common::Vector2D<double>(direction.x, direction.y));
    ecsWorld.getComponent<BodyComponent>(entity).body->applyForce(common::Vector2D<double>(0, 0), playerPosition);

    return projectileEntity;
}

namespace game {
namespace systems {

    WeaponSystem::WeaponSystem(engine::ecs::World& ecsWorld, engine::physics::World& physicsWorld, engine::input::InputManager& inputManager, engine::graphics::Camera& camera)
        : m_ecsWorld(ecsWorld)
        , m_physicsWorld(physicsWorld)
        , m_inputMaps(inputManager.getMap())
        , m_camera(camera)
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

                const auto& inputMap = m_inputMaps.getMap(inputComponent.controllerId);
                const auto action = definitions::Action::UseWeapon;
                const auto control = inputComponent.getKey(action);
                const auto analogControl = inputComponent.getAnalog(action);

                if (inputMap.getValue(analogControl) > 1) {
                    //auto test = common::Vector2D<double>(0, 0);
                    //shoot(entity, weapon, test);
                }

                if (inputMap.hasKeyState(control, engine::input::KeyStates::DOWN)) {
                    auto testr = common::Vector2D<int>(inputMap.getValue(engine::input::AnalogKeys::MOUSE_X), inputMap.getValue(engine::input::AnalogKeys::MOUSE_Y));
                    auto testrr = calculateDirection(entity, testr);
                    shoot(entity, weapon, testrr);
                }
            }
        });
    }

    void WeaponSystem::shoot(engine::ecs::Entity& entity, game::components::WeaponComponent& weapon, common::Vector2D<double>& test)
    {
        using milliseconds = std::chrono::milliseconds;
        double secondsSinceFired = std::chrono::duration_cast<milliseconds>(weapon.timeSinceLastFired).count() / 1000.0;
        if (!weapon.wasFired || secondsSinceFired > weapon.cooldownSeconds) {
            if (fireFunctionMap.find(weapon.type) != fireFunctionMap.end()) {
                auto& position = m_ecsWorld.getComponent<PositionComponent>(entity);
                fireFunctionMap[weapon.type](entity, position.position, m_physicsWorld, m_ecsWorld, test);
                weapon.timeSinceLastFired = std::chrono::nanoseconds(0);
                weapon.wasFired = true;
            }
        }
    }

    common::Vector2D<double> WeaponSystem::calculateDirection(engine::ecs::Entity& entity, common::Vector2D<int>& direction)
    {
        auto playerPosition = m_camera.translatePosition(m_ecsWorld.getComponent<PositionComponent>(entity).position);

        direction.x -= playerPosition.x;
        direction.y -= playerPosition.y;

        auto normalizedDirection = direction.normalize();
        normalizedDirection.x = normalizedDirection.x * 20;
        normalizedDirection.y = -normalizedDirection.y * 20;
        /*
        auto doublex = (double)direction.x;
        auto doubley = -(double)direction.y;

        double pytA = doublex * doublex;
        double pytB = doubley * doubley;
        double pytC = pytA + pytB;

        pytC = sqrt(pytC);
        pytA = (doublex / pytC) * 20;
        pytB = (doubley / pytC) * 20;

        std::cout << pytA << " " << pytB << std::endl;*/
        return normalizedDirection; //common::Vector2D<double>(pytA, pytB);
    }

    void WeaponSystem::render(engine::IRenderer& /* renderer */) {}
}
}
