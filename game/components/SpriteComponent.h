#pragma once

#include <engine/ecs/Component.h>
#include <string>

namespace game {
namespace components {
    struct SpriteComponent : public engine::BaseComponent<SpriteComponent> {
        std::string sheetPath, spriteName;

        SpriteComponent(std::string sheetPath, std::string spriteName)
            : sheetPath(sheetPath),
              spriteName(spriteName)
              {};
    };
}
}
