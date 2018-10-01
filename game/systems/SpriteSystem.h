#pragma once

#include "engine/ecs/System.h"

namespace game {
namespace systems {
    class SpriteSystem : public engine::BaseSystem<SpriteSystem> {
    public:
        SpriteSystem();

        void update(double frameTime) override;
    };
}
}
