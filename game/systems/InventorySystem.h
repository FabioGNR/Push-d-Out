#pragma once

#include "game/components/InventoryComponent.h"
#include <ecs/World.h>
#include <engine/ecs/System.h>
#include <engine/input/InputManager.h>

namespace game {
namespace systems {
    class InventorySystem : public engine::ecs::BaseSystem<InventorySystem> {
    private:
        const double PICKUP_RANGE = 3;
        engine::ecs::World& m_world;
        engine::input::KeyMap m_keyMap;

        void attemptPickup(engine::ecs::Entity& player, components::InventoryComponent& inventoryComponent);

    public:
        InventorySystem(engine::ecs::World& world, engine::input::InputManager& inputManager);

        void update(std::chrono::nanoseconds timeStep) override;
        void render(engine::IRenderer& renderer) override;
    };
}
}