#include "LevelReader.h"

#include "game/components/BodyComponent.h"
#include "game/components/CharacterSpawnComponent.h"
#include "game/components/DimensionComponent.h"
#include "game/components/EquipableComponent.h"
#include "game/components/LevelMetaComponent.h"
#include "game/components/PositionComponent.h"
#include "game/components/SpriteComponent.h"
#include "game/systems/PositionSystem.h"
#include "game/systems/SpriteSystem.h"

#include <engine/exceptions/ResourceNotFoundException.h>
#include <fstream>

namespace game {
namespace level {
    json LevelReader::readJSON(const std::string& fileName)
    {
        std::ifstream i(fileName);
        if (!i.good()) {
            throw ResourceNotFoundException(fileName);
        }
        json j;
        i >> j;
        return j;
    }

    Level LevelReader::getLevel(const json& j)
    {
        Level level = j;
        return level;
    }

    void LevelReader::createEntities(engine::ecs::World& world, engine::physics::World& physics, Level level)
    {
        common::Vector2D<double> dimension{ 1, 1 };

        auto& entityMeta = world.createEntity();
        auto levelMetaComponent = components::LevelMetaComponent(level.name, level.theme, level.height, level.width);
        world.addComponent<components::LevelMetaComponent>(entityMeta, levelMetaComponent);

        world.addSystem<systems::PositionSystem>(engine::definitions::SystemPriority::Medium, world);
        world.addSystem<systems::SpriteSystem>(engine::definitions::SystemPriority::Medium);

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
            auto spriteComponent = components::SpriteComponent(getSheetName(level.theme), curTile.sprite);
            world.addComponent<components::SpriteComponent>(entity, spriteComponent);

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
            auto spriteComponent = components::SpriteComponent(getSheetName(level.theme), "characterSpawn");
            world.addComponent<components::SpriteComponent>(entity, spriteComponent);

            // Add a character spawn component to character spawn entity
            auto characterSpawnComponent = components::CharacterSpawnComponent();
            world.addComponent<components::CharacterSpawnComponent>(entity, characterSpawnComponent);
        }

        for (size_t i = 0; i < level.EquipmentSpawns.size(); i++) {
            SpawnPoint curSpawn = level.EquipmentSpawns[i];
            common::Vector2D<double> position{ curSpawn.x, curSpawn.y };
            auto& entity = world.createEntity();
            // Add a position component to equipment spawn entity
            auto posComponent = components::PositionComponent(position);
            world.addComponent<components::PositionComponent>(entity, posComponent);
            // Add a dimension component to equipment spawn entity
            auto dimensionComponent = components::DimensionComponent(common::Vector2D<double>(1, 1));
            world.addComponent<components::DimensionComponent>(entity, dimensionComponent);
            // Add a sprite component to equipment spawn entity
            auto spriteComponent = components::SpriteComponent(getSheetName(level.theme), "equipmentSpawn");
            world.addComponent<components::SpriteComponent>(entity, spriteComponent);
            // Add a equipable component to equipment spawn entity
            auto equipableComponent = components::EquipableComponent();
            world.addComponent<components::EquipableComponent>(entity, equipableComponent);
        }
    }
}
}
