#pragma once

#include "Reader.h"
#include "external/JSON/json.hpp"
#include "game/level/LevelDomain.h"
#include <engine/ecs/World.h>
#include <engine/physics/World.h>
#include <string>

namespace game {
namespace level {
    using json = nlohmann::json;

    class LevelReader : public Reader<Level> {
    public:
        Level build(const json& j) override;

        static void createEntities(engine::ecs::World& world, engine::physics::World& physics, const Level& level);

    private:
        static void makePlatforms(engine::ecs::World& world, engine::physics::World& physics, const Level& level);
    };
}
}
