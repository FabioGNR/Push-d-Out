#include "Tiles.h"
#include <game/components/PositionComponent.h>
#include <game/components/TileComponent.h>

namespace game::level {
engine::ecs::Entity* Tiles::get(engine::ecs::World& world, common::Vector2D<int> position)
{
    auto end = world.end<components::TileComponent>();
    for (auto it = world.begin<components::TileComponent>(); it != end; ++it) {
        auto e = &world.getEntity(it->first);
        auto pos = world.getComponent<components::PositionComponent>(*e).position.castTo<int>();
        if (pos == position) {
            return e;
        }
    }

    return nullptr;
}
}
