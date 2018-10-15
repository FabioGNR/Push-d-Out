#pragma once

#include "external/JSON/json.hpp"
#include "game/level/LevelDomain.h"
#include <engine/ecs/World.h>
#include <engine/physics/World.h>
#include <string>

using namespace game::levelDomain;

namespace game {
using json = nlohmann::json;

class levelReader {
public:
    static json readJSON(std::string fileName);

    static level getLevel(json j);

    static void createEntities(engine::ecs::World& world, engine::physics::World& physics, level level);
};
}