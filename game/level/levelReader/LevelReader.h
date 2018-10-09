#pragma once

#include "external/JSON/json.hpp"
#include "engine/ecs/World.h"
#include <game/level/LevelDomain.h>
#include <string>

using namespace game::levelDomain;

namespace game {
using json = nlohmann::json;

class levelReader {
public:
    static json readJSON(std::string fileName);

    static level getLevel(json j);

    static engine::ecs::World createEntities(level level);
};
}