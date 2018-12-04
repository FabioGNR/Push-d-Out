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
        engine::input::maps::InputMaps& m_inputMaps;

        void attemptPickup(engine::ecs::Entity& player, components::InventoryComponent& inventoryComponent);
        void attemptSwitch(components::InventoryComponent& inventoryComponent);
        void placeInInventory(components::InventoryComponent& inventoryComponent, engine::ecs::Entity* equipment) const;

    public:
        InventorySystem(engine::ecs::World& world, engine::input::InputManager& inputManager);

        void update(std::chrono::nanoseconds timeStep) override;
        void render(engine::IRenderer& renderer) override;
    };
}
}