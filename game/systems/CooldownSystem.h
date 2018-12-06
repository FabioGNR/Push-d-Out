#pragma once

#include "engine/ecs/System.h"
#include "engine/ecs/World.h"

namespace game {
namespace systems {
    class CooldownSystem : public engine::ecs::BaseSystem<CooldownSystem> {
        engine::ecs::World& m_world;

    public:
        explicit CooldownSystem(engine::ecs::World& world)
            : m_world{ world } {};

        void update(std::chrono::nanoseconds timeStep) override;
        void render(engine::IRenderer& renderer) override;
    };
}
}
