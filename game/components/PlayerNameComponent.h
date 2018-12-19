#pragma once

#include "engine/ecs/Component.h"
#include <string>
#include <utility>

namespace game {
namespace components {
    struct PlayerNameComponent : public engine::ecs::BaseComponent<PlayerNameComponent> {
    public:
        explicit PlayerNameComponent(std::string playerName)
            : name{ std::move(playerName) }
        {
        }
        std::string name{};
    };
}
}
