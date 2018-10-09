#pragma once

#include "engine/ecs/System.h"

namespace game {
namespace systems {
    class SpriteSystem : public engine::ecs::BaseSystem<SpriteSystem> {
    public:
        SpriteSystem();

        void update(double frameTime) override;
    };
}
}
