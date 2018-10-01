#include "engine/ecs/World.h"
#include "engine/ecs/Entity.h"

engine::Entity& engine::World::createEntity()
{
    return m_entityManager.create();
}

void engine::World::destroyEntity(engine::Entity& entity)
{
    for (auto& manager : m_componentManager.getAll()) {
        manager.second->remove(entity);
    }
    m_entityManager.destroy(entity);
}