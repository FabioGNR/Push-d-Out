#include <exception>
#include <fstream>
#include <game/components/CharacterSpawnComponent.h>
#include <game/components/LevelMetaComponent.h>
#include <game/components/SpriteComponent.h>
#include <iostream>
#include <game/systems/PositionSystem.h>
#include <game/systems/BodySystem.h>
#include <game/systems/SpriteSystem.h>

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

engine::ecs::World levelReader::createEntities(level level)
{
    engine::ecs::World world;

    auto& entity = world.createEntity();
    auto levelMetaComponent = components::LevelMetaComponent(level.name, level.theme, level.height, level.width);
    world.addComponent<components::LevelMetaComponent>(entity, levelMetaComponent);

    world.addSystem<systems::PositionSystem>(engine::definitions::SystemPriority::Medium);
    world.addSystem<systems::BodySystem>(engine::definitions::SystemPriority::Medium);
    world.addSystem<systems::SpriteSystem>(engine::definitions::SystemPriority::Medium);

    for (size_t i = 0; i < level.tiles.size(); i++) {
        tile curTile = level.tiles[i];
        auto& entity = world.createEntity();

        // Add a position component to tile entity
        auto posComponent = components::PositionComponent(curTile.x, curTile.y);
        world.addComponent<components::PositionComponent>(entity, posComponent);

        // Add a body component to tile entity
        auto bodyComponent = components::BodyComponent(definitions::Body::Static);
        world.addComponent<components::BodyComponent>(entity, bodyComponent);

        // Add a sprite component to tile entity
        auto spriteComponent = components::SpriteComponent(levelDomain::getSheetName(level.theme), curTile.sprite);
        world.addComponent<components::SpriteComponent>(entity, spriteComponent);
    }

    for (size_t i = 0; i < level.CharacterSpawns.size(); i++) {
        spawnPoint curSpawn = level.CharacterSpawns[i];
        auto& entity = world.createEntity();

        // Add a position component to characterspawn entity
        auto posComponent = components::PositionComponent(curSpawn.x, curSpawn.y);
        world.addComponent<components::PositionComponent>(entity, posComponent);

        // Add a sprite component to characterspawn entity
        auto spriteComponent = components::SpriteComponent(levelDomain::getSheetName(level.theme), "characterSpawn");
        world.addComponent<components::SpriteComponent>(entity, spriteComponent);

        // Add a characterspawn component to characterspawn entity
        auto characterSpawnComponent = components::CharacterSpawnComponent();
        world.addComponent<components::CharacterSpawnComponent>(entity, characterSpawnComponent);
    }
    return world;
}
}
