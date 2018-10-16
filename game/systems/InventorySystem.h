#pragma once

#include <ecs/World.h>
#include <engine/ecs/System.h>
#include "game/components/InventoryComponent.h"

namespace game {
namespace systems {
    class InventorySystem : public engine::ecs::BaseSystem<InventorySystem> {
    private:
        const double PICKUP_RANGE = 3;
        engine::ecs::World& m_world;

        void attemptPickup(engine::ecs::Entity& player, components::InventoryComponent& inventoryComponent);

    public:
        InventorySystem(engine::ecs::World& world)
            : m_world{ world } {};

        void update(std::chrono::nanoseconds timeStep) override;
        void render(engine::IRenderer& renderer) override;
    };
}
}