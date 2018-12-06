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
        try {
            return m_entityManager.entity(id);
        } catch (...) {
            throw; // probably entity not found
        }
    }

    void World::destroyEntity(Entity& entity)
    {
        for (auto& manager : m_componentManager.getAll()) {
            manager.second->remove(entity);
        }
        m_entityManager.destroy(entity);
    }

    void World::destroyEntityNextUpdate(Entity& entity)
    {
        m_entitiesToDestroy.push_back(entity.id());
    }

    void World::update(std::chrono::nanoseconds timeStep)
    {
        std::for_each(m_entitiesToDestroy.begin(), m_entitiesToDestroy.end(), [&](auto& id) {
            try {
                auto& entity = getEntity(id);
                destroyEntity(entity);
            } catch (...) {
                // entity not found
            }
        });
        m_entitiesToDestroy.clear();

        m_systemManager.update(timeStep);
    }

    void World::render(engine::IRenderer& renderer)
    {
        m_systemManager.render(renderer);
    }
}
}
