

#pragma once
#include <utility>
#include "IBuilder.h"
#include "../components/SpriteComponent.h"

namespace game {
namespace builders {
    class SpriteBuilder {
    protected:
        std::string spriteSheetPath;
        std::string jsonFile;
    public:
        explicit SpriteBuilder(std::string spriteSheetPath, std::string jsonFile)
        : spriteSheetPath{std::move(spriteSheetPath)}
        , jsonFile{std::move(jsonFile)}
        {};

        std::map<std::string, components::SpriteComponent> build() const;
    };
}
}
