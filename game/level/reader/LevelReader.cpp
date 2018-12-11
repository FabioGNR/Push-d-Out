#include "LevelReader.h"

#include "game/builders/SpriteBuilder.h"
#include "game/components/BodyComponent.h"
#include "game/components/CharacterSpawnComponent.h"
#include "game/components/DimensionComponent.h"
#include "game/components/EquipableComponent.h"
#include "game/components/EquipmentSpawnerComponent.h"
#include "game/components/LevelMetaComponent.h"
#include "game/components/PositionComponent.h"
#include "game/components/SpriteComponent.h"
#include "game/systems/EquipmentSpawnSystem.h"
#include "game/systems/PositionSystem.h"
#include <iostream>

namespace game {
namespace level {
    Level LevelReader::build(const json& j)
    {
        Level level = j;
        return level;
    }

    void LevelReader::createEntities(engine::ecs::World& world, engine::physics::World& physics, const Level& level)
    {
        std::string basePath{ "assets/sprites/" };
        std::string baseThemePath{ basePath + "themes/" };
        std::string levelSheet{ level.theme.sprites };

        auto& entityMeta = world.createEntity();
        auto levelMetaComponent = components::LevelMetaComponent(level.name, level.theme);
        auto levelBoundsComponent = components::DimensionComponent(common::Vector2D<double>(level.width, level.height));
        world.addComponent<components::LevelMetaComponent>(entityMeta, levelMetaComponent);
        world.addComponent<components::DimensionComponent>(entityMeta, levelBoundsComponent);

        world.addSystem<systems::PositionSystem>(engine::definitions::SystemPriority::Medium, world);

        // Get a map with tile animations
        builders::SpriteBuilder tileSpriteBuilder{ baseThemePath + levelSheet + "/" + levelSheet + ".png", baseThemePath + "datafile.json" };
        auto tileSpriteComponentMap = tileSpriteBuilder.build();

        // Get a map with character spawn animations
        builders::SpriteBuilder charSpawnSpriteBuilder{ baseThemePath + levelSheet + "/" + levelSheet + ".png", baseThemePath + "datafile.json" };
        auto charSpawnSpriteComponentMap = charSpawnSpriteBuilder.build();

        // Get a map with equipment spawn animations
        builders::SpriteBuilder miscSpriteBuilder{ basePath + "misc/misc.png", basePath + "misc/misc.json" };
        auto miscSpriteComponentMap = miscSpriteBuilder.build();

        makePlatforms(world, physics, level);

        for (const auto& curSpawn : level.CharacterSpawns) {
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
        for (const auto& curSpawn : level.EquipmentSpawns) {
            common::Vector2D<double> position{ curSpawn.x, curSpawn.y };
            auto& entity = world.createEntity();
            // Add a position component to equipment spawn entity
            auto posComponent = components::PositionComponent(position);
            world.addComponent<components::PositionComponent>(entity, posComponent);
            // Add a dimension component to equipment spawn entity
            auto dimensionComponent = components::DimensionComponent(common::Vector2D<double>(1.2, 0.4));
            world.addComponent<components::DimensionComponent>(entity, dimensionComponent);

            // Add a sprite component to equipment spawn entity
            auto spriteComponentPair = miscSpriteComponentMap.find("EquipmentSpawner");
            if (spriteComponentPair != miscSpriteComponentMap.end()) {
                auto spriteComponent = spriteComponentPair->second;
                world.addComponent<components::SpriteComponent>(entity, spriteComponent);
            }

            // Add an equipment spawner component to equipment spawn entity
            auto spawnerComponent = components::EquipmentSpawnerComponent(10);
            world.addComponent<components::EquipmentSpawnerComponent>(entity, spawnerComponent);
        }
    }

    void LevelReader::makePlatforms(engine::ecs::World& world, engine::physics::World& physics, const Level& level)
    {
        std::string basePath{ "assets/sprites/themes/" };
        std::string levelSheet{ level.theme.sprites };

        builders::SpriteBuilder tileSpriteBuilder{ basePath + levelSheet + "/" + levelSheet + ".png", basePath + "datafile.json" };
        auto tileSpriteComponentMap = tileSpriteBuilder.build();

        auto remainingTiles = level.tiles;
        const auto defaultTileSize = common::Vector2D<double>{ 1, 1 };

        while (!remainingTiles.empty()) {
            auto& currentTile = remainingTiles[0];
            common::Vector2D<double> bodySize{ 1, 1 };

            Tile* nextTile = nullptr;
            do {
                auto nextTileCandidate = std::find_if(remainingTiles.begin(), remainingTiles.end(), [&](const auto& other) {
                    return std::abs(currentTile.x - (other.x - bodySize.x)) < 0.1
                        && std::abs(other.y - currentTile.y) < 0.1;
                });
                if (nextTileCandidate != remainingTiles.end()) {
                    nextTile = &*nextTileCandidate;
                    bodySize.x += defaultTileSize.x;

                    auto& entity = world.createEntity();
                    common::Vector2D<double> position{ nextTile->x, nextTile->y };

                    // Add a position component to tile entity
                    auto posComponent = components::PositionComponent(position);
                    world.addComponent<components::PositionComponent>(entity, posComponent);

                    // Add a sprite component to tile entity
                    auto spriteComponentPair = tileSpriteComponentMap.find(nextTile->sprite);
                    if (spriteComponentPair != tileSpriteComponentMap.end()) {
                        auto spriteComponent = spriteComponentPair->second;
                        world.addComponent<components::SpriteComponent>(entity, spriteComponent);
                    }

                    auto dimensionComponent = components::DimensionComponent(defaultTileSize);
                    world.addComponent<components::DimensionComponent>(entity, dimensionComponent);

                    remainingTiles.erase(nextTileCandidate);
                } else {
                    nextTile = nullptr;
                }
            } while (nextTile != nullptr);

            auto& entity = world.createEntity();
            common::Vector2D<double> position{ currentTile.x, currentTile.y };

            // Add a position component to tile entity
            auto posComponent = components::PositionComponent(position);
            world.addComponent<components::PositionComponent>(entity, posComponent);

            // Add a body component to tile entity
            auto bodyComponent = components::BodyComponent(physics.createStaticBody(position, bodySize, entity.id()));
            world.addComponent<components::BodyComponent>(entity, std::move(bodyComponent));

            // Add a sprite component to tile entity
            auto spriteComponentPair = tileSpriteComponentMap.find(currentTile.sprite);
            if (spriteComponentPair != tileSpriteComponentMap.end()) {
                auto spriteComponent = spriteComponentPair->second;
                world.addComponent<components::SpriteComponent>(entity, spriteComponent);
            }

            auto dimensionComponent = components::DimensionComponent(defaultTileSize);
            world.addComponent<components::DimensionComponent>(entity, dimensionComponent);

            remainingTiles.erase(remainingTiles.begin());
        }
    }
}
}
