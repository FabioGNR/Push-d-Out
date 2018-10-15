#pragma once

#include "game/level/LevelDomain.h"
#include <ecs/Component.h>
#include <string>

namespace game {
namespace components {
    struct LevelMetaComponent : public engine::ecs::BaseComponent<LevelMetaComponent> {
        std::string name;
        levelDomain::Theme theme;
        int height, width;

        LevelMetaComponent(std::string name, levelDomain::Theme theme, int height, int width)
            : name(name)
            , theme(theme)
            , height(height)
            , width(width){};
    };
}
}