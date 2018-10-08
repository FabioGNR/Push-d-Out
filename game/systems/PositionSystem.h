#pragma once

#include "engine/ecs/System.h"

namespace game {
namespace systems {
    class PositionSystem : public engine::BaseSystem<PositionSystem> {
    public:
        PositionSystem();

        void update(double frameTime) override;
    };
}
}
