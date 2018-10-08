#include <exception>
#include <fstream>
#include <iostream>
#include <game/components/SpriteComponent.h>
#include <game/components/CharacterSpawnComponent.h>

#include "LevelReader.h"
#include "engine/ecs/World.h"
#include "game/components/PositionComponent.h"
#include "game/components/BodyComponent.h"
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

engine::World levelReader::createEntities(level level)
{
    auto world = engine::World();

    for (int i = 0; i < level.tiles.size(); i++) {
        tile curTile = level.tiles[i];
        auto& entity = world.createEntity();

        auto posComponent = components::PositionComponent(curTile.x, curTile.y);
        world.addComponent<components::PositionComponent>(entity, posComponent);
        auto bodyComponent = components::BodyComponent(definitions::Body::Static);
        world.addComponent<components::BodyComponent>(entity, bodyComponent);
        auto spriteComponent = components::SpriteComponent(levelDomain::getSheetName(level.theme), curTile.sprite);
        world.addComponent<components::SpriteComponent>(entity, spriteComponent);
    }

    for (int i = 0; i < level.CharacterSpawns.size(); i++) {
        spawnPoint curSpawn = level.CharacterSpawns[i];
        auto& entity = world.createEntity();

        auto posComponent = components::PositionComponent(curSpawn.x, curSpawn.y);
        world.addComponent<components::PositionComponent>(entity, posComponent);
        auto spriteComponent = components::SpriteComponent(levelDomain::getSheetName(level.theme), "characterSpawn");
        world.addComponent<components::SpriteComponent>(entity, spriteComponent);
        auto characterSpawnComponent = components::CharacterSpawnComponent();
        world.addComponent<components::CharacterSpawnComponent>(entity, characterSpawnComponent);
    }
    return world;
}
}
