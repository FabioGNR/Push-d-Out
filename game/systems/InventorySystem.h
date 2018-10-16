#pragma once

#include <ecs/World.h>
#include <engine/ecs/System.h>

namespace game {
namespace systems {
    class InventorySystem : public engine::ecs::BaseSystem<InventorySystem> {
    private:
        engine::ecs::World& m_world;

        void attemptPickup(engine::ecs::Entity& player) const;

    public:
        InventorySystem(engine::ecs::World& world)
            : m_world{ world } {};

        void update(std::chrono::nanoseconds timeStep) override;
        void render(engine::IRenderer& renderer) override;
    };
}
}