#pragma once

#include "engine/ecs/System.h"

namespace game {
namespace systems {
    class JumpSystem : public engine::BaseSystem<JumpSystem> {
    public:
        JumpSystem();

        void update(double frameTime) override;
    };
}
}
