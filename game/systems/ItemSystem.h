#pragma once
#include <game/definitions/Action.h>
#include <game/definitions/ItemType.h>

#include <engine/ecs/Entity.h>
#include <engine/ecs/System.h>
#include <engine/ecs/World.h>
#include <engine/input/InputManager.h>
#include <engine/physics/World.h>

namespace game {
namespace systems {
    class ItemSystem : public engine::ecs::BaseSystem<ItemSystem> {
        engine::ecs::World& m_ecsWorld;
        engine::physics::World& m_physicsWorld;
        engine::input::maps::InputMap& m_inputMap;
        std::map<definitions::ItemType, std::function<void(engine::ecs::Entity&, engine::physics::World&, engine::ecs::World&)>> activateFunctionMap;
        //std::shared_ptr<engine::events::Subscription<engine::input::maps::AnalogMap>> m_inputSubscription;

    public:
        ItemSystem(engine::ecs::World& ecsWorld, engine::physics::World& physicsWorld, engine::input::InputManager& inputManager);

        void update(std::chrono::nanoseconds timeStep) override;
        void render(engine::IRenderer& renderer) override;
    };
}
}
