#include "ProjectileDestroyerSystem.h"
#include "GarbageCollectorSystem.h"
#include <game/components/DestructibleComponent.h>
#include <game/components/DimensionComponent.h>
#include <game/components/LevelMetaComponent.h>
#include <game/components/PositionComponent.h>
#include <game/components/ProjectileComponent.h>
#include <vector>

namespace game::systems {
using namespace components;

void ProjectileDestroyerSystem::update(std::chrono::nanoseconds /* timestep */)
{
    const int margin = 5;
    const auto& levelDimensions = getLevelDimensions();
    m_ecsWorld->forEachEntityWith<PositionComponent, DimensionComponent, ProjectileComponent>([&](engine::ecs::Entity& entity) {
        const auto& position = m_ecsWorld->getComponent<PositionComponent>(entity).position;
        const auto& dimension = m_ecsWorld->getComponent<DimensionComponent>(entity).dimension;
        bool xOutOfBounds = position.x > levelDimensions.x + margin || position.x + dimension.x < -margin;
        bool yOutOfBounds = position.y > levelDimensions.y + margin || position.y + dimension.y < -margin;
        if (!(xOutOfBounds || yOutOfBounds)) {
            return; // projectile is still in the level bounds
        }
        if (m_camera->isRectangleVisible(position, dimension)) {
            return; // won't delete visible projectiles
        }
        // mark the component as destructible so it gets destroyed
        markEntityDestructible(entity);
    });
}

void ProjectileDestroyerSystem::render(engine::IRenderer& /*renderer*/)
{
    // no rendering
}

common::Vector2D<double> ProjectileDestroyerSystem::getLevelDimensions() const
{
    common::Vector2D<double> levelBounds{ 0, 0 };
    m_ecsWorld->forEachEntityWith<LevelMetaComponent, DimensionComponent>([&](engine::ecs::Entity& levelEntity) {
        levelBounds = m_ecsWorld->getComponent<DimensionComponent>(levelEntity).dimension;
    });
    return levelBounds;
}

void ProjectileDestroyerSystem::markEntityDestructible(engine::ecs::Entity& entity)
{
    DestructibleComponent destructibleComponent{};
    m_ecsWorld->addComponent<DestructibleComponent>(entity, destructibleComponent);
}
}