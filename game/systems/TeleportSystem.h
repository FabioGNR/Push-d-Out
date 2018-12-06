#pragma once

#include <engine/ecs/System.h>
#include <engine/ecs/World.h>

namespace game {
namespace systems {
    class TeleportSystem : public engine::ecs::BaseSystem<TeleportSystem> {
    private:
        engine::ecs::World* m_ecsWorld;

    public:
        explicit TeleportSystem(engine::ecs::World* ecs)
            : m_ecsWorld{ ecs } {};

        void update(std::chrono::nanoseconds timeStep) override;
        void render(engine::IRenderer& renderer) override;
    };
}
}
