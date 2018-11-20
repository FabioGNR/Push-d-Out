#pragma once

#include "external/JSON/json.hpp"
#include <engine/common/Vector2D.h>
#include <string>

using json = nlohmann::json;

namespace game {
namespace sprite {
    struct Animation {
        std::string name;
        int frameCount;
        double frameTime;
        common::Vector2D<int> frameSize;
        common::Vector2D<int> topLeft;
        common::Vector2D<int> offset;
    };

    struct SpriteResource {
        SpriteResource(std::string spriteSheet, common::Vector2D<int> position, common::Vector2D<int> size, common::Vector2D<int> offset)
            : spriteSheet { std::move(spriteSheet) }
            , position { position }
            , size{ size }
            , offset { offset }
        {
        }
        std::string spriteSheet;
        common::Vector2D<int> position;
        common::Vector2D<int> offset;
        common::Vector2D<int> size;
    };

    struct AnimationList {
        std::vector<Animation> animations;
    };

    void to_json(json& j, const common::Vector2D<int>& v);
    void from_json(const json& j, common::Vector2D<int>& v);

    void to_json(json& j, const Animation& a);
    void from_json(const json& j, Animation& a);

    void to_json(json& j, const AnimationList& l);
    void from_json(const json& j, AnimationList& l);
}
}
