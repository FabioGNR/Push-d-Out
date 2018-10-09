#pragma once

#include "engine/ecs/System.h"

namespace game {
namespace systems {
class MoveSystem : public engine::ecs::BaseSystem<MoveSystem> {
    public:
        MoveSystem();

        void update(double frameTime) override;
    };
}
}
