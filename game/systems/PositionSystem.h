#pragma once

#include "engine/ecs/System.h"

namespace game {
namespace systems {
    class PositionSystem : public engine::ecs::BaseSystem<PositionSystem> {
    public:
        PositionSystem();

        void update(double frameTime) override;
    };
}
}
