#pragma once

#include <engine/common/Vector2D.h>
#include <engine/ecs/World.h>

namespace game {
namespace builders {
    class CharacterSpawnGenerator {
    public:
        CharacterSpawnGenerator() = delete;
        ~CharacterSpawnGenerator() = delete;
        static std::vector<common::Vector2D<double>> collect(engine::ecs::World& world);
    };
}
}
