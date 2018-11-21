#include <utility>

#pragma once

#include "game/level/LevelDomain.h"

#include <engine/ecs/Component.h>
#include <string>
#include <utility>
namespace game {
namespace components {
    struct LevelMetaComponent : public engine::ecs::BaseComponent<LevelMetaComponent> {
        std::string name;
        level::Theme theme;
        int height, width;

        LevelMetaComponent(std::string name, level::Theme theme, int height, int width)
            : name(std::move(name))
            , theme(std::move(std::move(theme)))
            , height(height)
            , width(width){};
    };
}
}