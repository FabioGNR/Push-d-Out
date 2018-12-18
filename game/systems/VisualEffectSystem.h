#pragma once

#include <engine/ecs/System.h>
#include <engine/ecs/World.h>

namespace game {
namespace systems {
    class VisualEffectSystem : public engine::ecs::BaseSystem<VisualEffectSystem> {
    private:
        engine::ecs::World* m_ecsWorld;

    public:
        explicit VisualEffectSystem(engine::ecs::World* ecs)
            : m_ecsWorld{ ecs } {};

        void update(std::chrono::nanoseconds timeStep) override;
        void render(engine::IRenderer& renderer) override;
    };
}
}
