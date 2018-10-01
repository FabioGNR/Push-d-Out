#pragma once

#include "engine/ecs/System.h"

namespace game {
namespace systems {
    class PlayerInputSystem : public engine::BaseSystem<PlayerInputSystem> {
    public:
        PlayerInputSystem();

        void update(double frameTime) override;
    };
}
}
