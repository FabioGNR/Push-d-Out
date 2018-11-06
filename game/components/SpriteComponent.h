#pragma once

#include <engine/ecs/Component.h>
#include <string>

namespace game {
namespace components {
    struct SpriteComponent : public engine::ecs::BaseComponent<SpriteComponent> {
        std::string sheetPath, spriteName;

        SpriteComponent(std::string sheetPath, std::string spriteName)
            : sheetPath(std::move(sheetPath))
            , spriteName(std::move(spriteName)){};
    };
}
}
