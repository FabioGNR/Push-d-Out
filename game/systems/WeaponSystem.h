#pragma once

#include "engine/graphics/Camera.h"
#include <engine/ecs/Entity.h>
#include <engine/ecs/System.h>
#include <engine/ecs/World.h>
#include <engine/input/InputManager.h>
#include <engine/physics/World.h>
#include <game/components/DirectionComponent.h>
#include <game/components/WeaponComponent.h>
#include <game/definitions/Action.h>
#include <game/definitions/WeaponType.h>

namespace game {
namespace systems {
    class WeaponSystem : public engine::ecs::BaseSystem<WeaponSystem> {
    private:
        engine::ecs::World& m_ecsWorld;
        engine::physics::World& m_physicsWorld;
        engine::input::maps::InputMaps& m_inputMaps;
        engine::graphics::Camera& m_camera;

        std::map<definitions::WeaponType, std::function<engine::ecs::Entity&(const engine::ecs::Entity&, const common::Vector2D<double>&, engine::physics::World&, engine::ecs::World&, common::Vector2D<double>& direction)>> fireFunctionMap;
        void shoot(const engine::ecs::Entity& entity, components::WeaponComponent& weapon, common::Vector2D<double> fireDirection);
        common::Vector2D<double> calculateDirection(const engine::ecs::Entity& entity, common::Vector2D<int>& direction, const game::components::DirectionComponent& directionComponent);

    public:
        WeaponSystem(engine::ecs::World& ecsWorld, engine::physics::World& physicsWorld, engine::input::InputManager& inputManager, engine::graphics::Camera& camera);

        void update(std::chrono::nanoseconds timeStep) override;
        void render(engine::IRenderer& renderer) override;
    };
}
}
