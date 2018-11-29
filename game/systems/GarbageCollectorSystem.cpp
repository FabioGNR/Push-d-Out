#include "GarbageCollectorSystem.h"
#include <game/components/BodyComponent.h>
#include <game/components/DestructibleComponent.h>
#include <game/components/DimensionComponent.h>
#include <game/components/LevelMetaComponent.h>
#include <game/components/PositionComponent.h>
#include <vector>

namespace game::systems {
void GarbageCollectorSystem::update(std::chrono::nanoseconds /* timestep */)
{
    // we need to delete the entities outside the forEach
    // as we would otherwise modify the iterator while iterating
    std::vector<engine::ecs::Entity*> entitiesToCollect;
    m_ecsWorld->forEachEntityWith<components::DestructibleComponent>([&](engine::ecs::Entity& entity) {
        entitiesToCollect.push_back(&entity);
    });
    std::for_each(entitiesToCollect.begin(), entitiesToCollect.end(), [&](auto* entity) {
        cleanUpEntity(entity);
    });
}

void GarbageCollectorSystem::render(engine::IRenderer& /*renderer*/)
{
    // no rendering
}

void GarbageCollectorSystem::cleanUpEntity(engine::ecs::Entity* entityToDestroy)
{
    if (entityToDestroy->hasComponent<components::BodyComponent>()) {
        auto* body = m_ecsWorld->getComponent<components::BodyComponent>(*entityToDestroy).body;
        m_physWorld->destroyBody(body);
    }
    m_ecsWorld->destroyEntity(*entityToDestroy);
}
}