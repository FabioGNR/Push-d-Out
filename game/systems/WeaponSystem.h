#pragma once

#include <game/definitions/Action.h>
#include <game/definitions/WeaponType.h>

#include <engine/ecs/Entity.h>
#include <engine/ecs/System.h>
#include <engine/ecs/World.h>
#include <engine/input/InputManager.h>
#include <engine/physics/World.h>
#include <game/components/WeaponComponent.h>

namespace game {
namespace systems {
    class WeaponSystem : public engine::ecs::BaseSystem<WeaponSystem> {
    private:
        engine::ecs::World& m_ecsWorld;
        engine::physics::World& m_physicsWorld;
        engine::input::maps::InputMap& m_inputMap;
        std::map<definitions::WeaponType, std::function<engine::ecs::Entity&(const engine::ecs::Entity&, const common::Vector2D<double>&, engine::physics::World&, engine::ecs::World&)>> fireFunctionMap;
        void shoot(engine::ecs::Entity& entity, components::WeaponComponent& weapon);

    public:
        WeaponSystem(engine::ecs::World& ecsWorld, engine::physics::World& physicsWorld, engine::input::InputManager& inputManager);

        void update(std::chrono::nanoseconds timeStep) override;
        void render(engine::IRenderer& renderer) override;
    };
}
}
