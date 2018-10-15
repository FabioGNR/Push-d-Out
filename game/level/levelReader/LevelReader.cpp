#include <exception>
#include <fstream>
#include <game/components/CharacterSpawnComponent.h>
#include <game/components/DimensionComponent.h>
#include <game/components/LevelMetaComponent.h>
#include <game/components/SpriteComponent.h>
#include <game/systems/PositionSystem.h>
#include <game/systems/SpriteSystem.h>
#include <iostream>

#include "LevelReader.h"
#include "engine/ecs/World.h"
#include "game/components/BodyComponent.h"
#include "game/components/PositionComponent.h"
#include "game/level/LevelDomain.h"

namespace game {
json levelReader::readJSON(std::string fileName)
{
    std::ifstream i(fileName);
    json j;
    i >> j;
    return j;
}

level levelReader::getLevel(json j)
{
    level level = j;
    return level;
}

void levelReader::createEntities(engine::ecs::World& world, engine::physics::World& physics, level level)
{
    const int TILE_WIDTH = 1;
    const int TILE_HEIGHT = 1;

    auto& entityMeta = world.createEntity();
    auto levelMetaComponent = components::LevelMetaComponent(level.name, level.theme, level.height, level.width);
    world.addComponent<components::LevelMetaComponent>(entityMeta, levelMetaComponent);

    world.addSystem<systems::PositionSystem>(engine::definitions::SystemPriority::Medium, world);
    world.addSystem<systems::SpriteSystem>(engine::definitions::SystemPriority::Medium);

    for (size_t i = 0; i < level.tiles.size(); i++) {
        tile curTile = level.tiles[i];
        auto& entity = world.createEntity();

        // Add a position component to tile entity
        common::Vector2D position { (double)curTile.x, (double)curTile.y };
        auto posComponent = components::PositionComponent(position);
        world.addComponent<components::PositionComponent>(entity, posComponent);

        // Add a body component to tile entity
        auto bodyComponent = components::BodyComponent(physics.createStaticBody(curTile.x, curTile.y, TILE_WIDTH, TILE_HEIGHT));
        world.addComponent<components::BodyComponent>(entity, bodyComponent);

        // Add a sprite component to tile entity
        auto spriteComponent = components::SpriteComponent(levelDomain::getSheetName(level.theme), curTile.sprite);
        world.addComponent<components::SpriteComponent>(entity, spriteComponent);

        common::Vector2D dimension { TILE_WIDTH, TILE_HEIGHT };
        auto dimensionComponent = components::DimensionComponent(dimension);
        world.addComponent<components::DimensionComponent>(entity, dimensionComponent);
    }

    for (size_t i = 0; i < level.CharacterSpawns.size(); i++) {
        spawnPoint curSpawn = level.CharacterSpawns[i];
        auto& entity = world.createEntity();

        // Add a position component to character spawn entity
        common::Vector2D position { (double)curSpawn.x, (double)curSpawn.y };
        auto posComponent = components::PositionComponent(position);
        world.addComponent<components::PositionComponent>(entity, posComponent);

        // Add a sprite component to character spawn entity
        auto spriteComponent = components::SpriteComponent(levelDomain::getSheetName(level.theme), "characterSpawn");
        world.addComponent<components::SpriteComponent>(entity, spriteComponent);

        // Add a character spawn component to character spawn entity
        auto characterSpawnComponent = components::CharacterSpawnComponent();
        world.addComponent<components::CharacterSpawnComponent>(entity, characterSpawnComponent);
    }
}
}
