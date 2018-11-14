#pragma once

#include <engine/ecs/System.h>
#include <engine/ecs/World.h>
#include <engine/input/InputManager.h>
#include <game/components/InventoryComponent.h>

namespace game {
namespace systems {
    class InventorySystem : public engine::ecs::BaseSystem<InventorySystem> {
    private:
        const double PICKUP_RANGE = 3;
        engine::ecs::World& m_world;
        engine::input::maps::InputMap& m_inputMap;
        //std::shared_ptr<engine::events::Subscription<engine::input::maps::AnalogMap>> m_inputSubscription;

        void attemptPickup(engine::ecs::Entity& player, components::InventoryComponent& inventoryComponent);

    public:
        InventorySystem(engine::ecs::World& world, engine::input::InputManager& inputManager);

        void update(std::chrono::nanoseconds timeStep) override;
        void render(engine::IRenderer& renderer) override;
    };
}
}