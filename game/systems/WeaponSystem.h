#pragma once

#include <game/definitions/Action.h>
#include <game/definitions/WeaponType.h>

#include <engine/ecs/Entity.h>
#include <engine/ecs/System.h>
#include <engine/ecs/World.h>
#include <engine/input/InputManager.h>
#include <engine/input/KeyMap.h>
#include <engine/physics/World.h>

namespace game {
namespace systems {
    class WeaponSystem : public engine::ecs::BaseSystem<WeaponSystem> {
        engine::ecs::World& m_ecsWorld;
        engine::physics::World& m_physicsWorld;
        engine::input::KeyMap m_keyMap;
        std::map<definitions::WeaponType, std::function<engine::ecs::Entity&(const engine::ecs::Entity&, const common::Vector2D<double>&, engine::physics::World&, engine::ecs::World&)>> fireFunctionMap;
        std::shared_ptr<engine::events::Subscription<engine::input::KeyMap>> m_inputSubscription;

    public:
        WeaponSystem(engine::ecs::World& ecsWorld, engine::physics::World& physicsWorld, engine::input::InputManager& inputManager);

        void update(std::chrono::nanoseconds timeStep) override;
        void render(engine::IRenderer& renderer) override;
    };
}
}
