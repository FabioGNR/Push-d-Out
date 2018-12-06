#pragma once

#include <engine/common/Vector2D.h>
#include <engine/ecs/Component.h>

namespace game {
namespace components {
    struct PortalComponent : public engine::ecs::BaseComponent<PortalComponent> {
        bool isPrimary = true;
        std::chrono::nanoseconds timeout{ 0 };
        std::chrono::nanoseconds cooldown{ 0 };

        PortalComponent() = default;
        explicit PortalComponent(bool primary, std::chrono::nanoseconds cooldown = std::chrono::seconds{ 1 })
            : isPrimary(primary)
            , cooldown(cooldown){};
    };
}
}
