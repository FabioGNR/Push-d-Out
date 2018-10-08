#pragma once

#include "engine/ecs/System.h"

namespace game {
namespace systems {
    class DimensionSystem : public engine::BaseSystem<DimensionSystem> {
    public:
        DimensionSystem();

        void update(double frameTime) override;
    };
}
}
