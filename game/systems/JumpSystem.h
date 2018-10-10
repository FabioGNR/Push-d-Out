#pragma once

#include "engine/ecs/System.h"

namespace game {
namespace systems {
    class JumpSystem : public engine::ecs::BaseSystem<JumpSystem> {
    public:
        JumpSystem();

        void update(std::chrono::nanoseconds timeStep) override;
        void render(engine::IRenderer& renderer) override;
    };
}
}
