#pragma once

#include "engine/ecs/Component.h"
#include "engine/graphics/drawable/Sprite.h"
#include "game/sprite/SpriteDomain.h"
#include <chrono>
#include <string>
#include <vector>

namespace game {
namespace components {
    struct SpriteComponent : public engine::ecs::BaseComponent<SpriteComponent> {
        std::vector<sprite::SpriteResource> sprites;
        int frameCount = 1, index = 0;
        double frameTime = 0.1;
        std::chrono::nanoseconds frameTimeElapsed{ 0 };
        bool isAnimated = false;

        SpriteComponent(std::vector<sprite::SpriteResource> sprites, int frameCount, double frameTime)
            : sprites{ move(sprites) }
            , frameCount{ frameCount }
            , frameTime{ frameTime }
            , isAnimated{ true } {};

        explicit SpriteComponent(sprite::SpriteResource sprite)
            : sprites{ std::move(sprite) } {};
    };
}
}
