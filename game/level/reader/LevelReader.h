#pragma once

#include "external/JSON/json.hpp"
#include "game/level/LevelDomain.h"
#include <engine/ecs/World.h>
#include <engine/physics/World.h>
#include <string>

namespace game {
namespace level {
    using json = nlohmann::json;

    class LevelReader {
    public:
        static json readJSON(const std::string& fileName);
        static Level getLevel(const json& j);
        static void createEntities(engine::ecs::World& world, engine::physics::World& physics, Level level);
    };
}
}
