#include "CharacterSpawnGenerator.h"
#include <game/components/CharacterSpawnComponent.h>
#include <game/components/PositionComponent.h>
#include <game/exceptions/MissingCharacterSpawnException.h>

namespace game {
namespace builders {
    std::vector<common::Vector2D<double>> CharacterSpawnGenerator::collect(engine::ecs::World& world)
    {
        // Search for all the CharacterSpawnComponents and push the position in the vector
        std::vector<common::Vector2D<double>> positions{};
        world.forEachEntityWith<components::CharacterSpawnComponent>([&](engine::ecs::Entity& entity) {
            auto component = world.getComponent<components::PositionComponent>(entity);
            auto pos = component.position;
            positions.push_back(pos);
        });

        return positions;
    }
}
}
