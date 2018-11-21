#include "engine/ecs/World.h"
#include "engine/ecs/Entity.h"

namespace engine {
namespace ecs {
    Entity& World::createEntity()
    {
        return m_entityManager.create();
    }

    Entity& World::getEntity(EntityId id)
    {
        return m_entityManager.entity(id);
    }

    void World::destroyEntity(Entity& entity)
    {
        for (auto& manager : m_componentManager.getAll()) {
            manager.second->remove(entity);
        }
        m_entityManager.destroy(entity);
    }

    void World::update(std::chrono::nanoseconds timeStep)
    {
        m_systemManager.update(timeStep);
    }

    void World::render(engine::IRenderer& renderer)
    {
        m_systemManager.render(renderer);
    }
}
}
