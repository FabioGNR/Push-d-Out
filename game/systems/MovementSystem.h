#pragma once

#include <engine/ecs/System.h>
#include <engine/ecs/World.h>

namespace game {
namespace systems {
    class MovementSystem : public engine::ecs::BaseSystem<MovementSystem> {
    private:
        engine::ecs::World& m_world;

    public:
        explicit MovementSystem(engine::ecs::World& world)
            : m_world{ world } {};

        void update(std::chrono::nanoseconds timeStep) override;
        void render(engine::IRenderer& renderer) override;
    };
}
}
