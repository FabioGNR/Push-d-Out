#include "LevelReader.h"
#include "game/builders/SpriteBuilder.h"
#include "game/components/BodyComponent.h"
#include "game/components/CharacterSpawnComponent.h"
#include "game/components/DimensionComponent.h"
#include "game/components/EquipmentSpawnerComponent.h"
#include "game/components/LevelMetaComponent.h"
#include "game/components/PositionComponent.h"
#include "game/components/SpriteComponent.h"
#include "game/systems/EquipmentSpawnSystem.h"
#include "game/systems/PositionSystem.h"
#include "game/systems/SpriteSystem.h"
#include <engine/exceptions/ResourceNotFoundException.h>
#include <fstream>
#include <game/components/EquipableComponent.h>

namespace game {
namespace level {
    Level LevelReader::build(const json& j)
    {
        Level level = j;
        return level;
    }

    void LevelReader::createEntities(engine::ecs::World& world, engine::physics::World& physics, Level level)
    {
        common::Vector2D<double> dimension{ 1, 1 };

        std::string basePath{ "assets/sprites/themes/" };
        std::string levelSheet{ level.theme.sprites };

        auto& entityMeta = world.createEntity();
        auto levelMetaComponent = components::LevelMetaComponent(level.name, level.theme, level.height, level.width);
        world.addComponent<components::LevelMetaComponent>(entityMeta, levelMetaComponent);

        world.addSystem<systems::PositionSystem>(engine::definitions::SystemPriority::Medium, world);
        world.addSystem<systems::SpriteSystem>(engine::definitions::SystemPriority::Medium);

        // Get a map with tile animations
        builders::SpriteBuilder tileSpriteBuilder{ basePath + levelSheet + "/" + levelSheet + ".png", basePath + "datafile.json" };
        auto tileSpriteComponentMap = tileSpriteBuilder.build();

        // Get a map with character spawn animations
        builders::SpriteBuilder charSpawnSpriteBuilder{ basePath + levelSheet + "/" + levelSheet + ".png", basePath + "datafile.json" };
        auto charSpawnSpriteComponentMap = charSpawnSpriteBuilder.build();

        // Get a map with equipment spawn animations
        builders::SpriteBuilder eqSpawnSpriteBuilder{ basePath + levelSheet + "/" + levelSheet + ".png", basePath + "datafile.json" };
        auto eqSpawnSpriteComponentMap = eqSpawnSpriteBuilder.build();

        for (size_t i = 0; i < level.tiles.size(); i++) {
            Tile curTile = level.tiles[i];
            common::Vector2D<double> position{ curTile.x, curTile.y };

            auto& entity = world.createEntity();

            // Add a position component to tile entity
            auto posComponent = components::PositionComponent(position);
            world.addComponent<components::PositionComponent>(entity, posComponent);

            // Add a body component to tile entity
            auto bodyComponent = components::BodyComponent(physics.createStaticBody(position, dimension));
            world.addComponent<components::BodyComponent>(entity, bodyComponent);

            // Add a sprite component to tile entity
            auto spriteComponentPair = tileSpriteComponentMap.find(curTile.sprite);
            if (spriteComponentPair != tileSpriteComponentMap.end()) {
                auto spriteComponent = spriteComponentPair->second;
                world.addComponent<components::SpriteComponent>(entity, spriteComponent);
            }

            auto dimensionComponent = components::DimensionComponent(dimension);
            world.addComponent<components::DimensionComponent>(entity, dimensionComponent);
        }

        for (size_t i = 0; i < level.CharacterSpawns.size(); i++) {
            SpawnPoint curSpawn = level.CharacterSpawns[i];
            common::Vector2D<double> position{ curSpawn.x, curSpawn.y };

            auto& entity = world.createEntity();

            // Add a position component to character spawn entity
            auto posComponent = components::PositionComponent(position);
            world.addComponent<components::PositionComponent>(entity, posComponent);

            // Add a sprite component to character spawn entity
            auto spriteComponentPair = charSpawnSpriteComponentMap.find("single");
            if (spriteComponentPair != charSpawnSpriteComponentMap.end()) {
                auto spriteComponent = spriteComponentPair->second;
                world.addComponent<components::SpriteComponent>(entity, spriteComponent);
            }

            // Add a character spawn component to character spawn entity
            auto characterSpawnComponent = components::CharacterSpawnComponent();
            world.addComponent<components::CharacterSpawnComponent>(entity, characterSpawnComponent);
        }

        world.addSystem<systems::EquipmentSpawnSystem>(engine::definitions::SystemPriority::Medium, world);

        for (size_t i = 0; i < level.EquipmentSpawns.size(); i++) {
            SpawnPoint curSpawn = level.EquipmentSpawns[i];
            common::Vector2D<double> position{ curSpawn.x, curSpawn.y };
            auto& entity = world.createEntity();
            // Add a position component to equipment spawn entity
            auto posComponent = components::PositionComponent(position);
            world.addComponent<components::PositionComponent>(entity, posComponent);
            // Add a dimension component to equipment spawn entity
            auto dimensionComponent = components::DimensionComponent(common::Vector2D<double>(0.8, 0.2));
            world.addComponent<components::DimensionComponent>(entity, dimensionComponent);

            // Add a sprite component to equipment spawn entity
            auto spriteComponentPair = eqSpawnSpriteComponentMap.find("single");
            if (spriteComponentPair != eqSpawnSpriteComponentMap.end()) {
                auto spriteComponent = spriteComponentPair->second;
                world.addComponent<components::SpriteComponent>(entity, spriteComponent);
            }

            // Add an equipment spawner component to equipment spawn entity
            auto spawnerComponent = components::EquipmentSpawnerComponent(10);
            world.addComponent<components::EquipmentSpawnerComponent>(entity, spawnerComponent);
        }
    }
}
}
