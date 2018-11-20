#pragma once

#include "external/JSON/json.hpp"
#include "game/sprite/SpriteDomain.h"
#include <string>

using json = nlohmann::json;

namespace game {
namespace sprite {
    class SpriteReader {
    public:
        static json readJSON(const std::string& jsonFileName);
        static std::map<std::string, Animation> getAnimationsFromJSON(const json& j);
    };
}
}
