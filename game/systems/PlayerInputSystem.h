#pragma once

#include "engine/ecs/System.h"

namespace game {
namespace systems {
    class PlayerInputSystem : public engine::ecs::BaseSystem<PlayerInputSystem> {
    public:
        PlayerInputSystem();

        void update(double frameTime) override;
    };
}
}
