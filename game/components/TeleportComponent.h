#pragma once

#include <engine/common/Vector2D.h>
#include <engine/ecs/Component.h>

namespace game {
namespace components {
    struct TeleportComponent : public engine::ecs::BaseComponent<TeleportComponent> {
        constexpr static std::chrono::nanoseconds COOLDOWN = std::chrono::nanoseconds{ 1'000'000'000 };

        common::Vector2D<double> position;
        bool enabled = true;
        bool inRange = true;
        std::chrono::nanoseconds timeout{ 0 };

        explicit TeleportComponent(common::Vector2D<double> vector)
            : position(vector){};
    };
}
}
