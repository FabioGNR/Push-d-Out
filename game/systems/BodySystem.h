#pragma once

#include "engine/ecs/System.h"

namespace game {
namespace systems {
    class BodySystem : public engine::BaseSystem<BodySystem> {
    public:
        BodySystem();

        void update(double frameTime) override;
    };
}
}
