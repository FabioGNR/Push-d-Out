#include "EntityManager.h"

#include <algorithm>
#include <utility>

namespace engine {
namespace ecs {
    Entity& EntityManager::create()
    {
        auto entity = std::make_unique<Entity>(makeUniqueEntityId());
        auto* entityPtr = entity.get();
        //m_entities.push_back(std::move(entity));
        m_entities.insert({ entityPtr->id(), std::move(entity) });

        return *entityPtr;
    }

    void EntityManager::destroy(const Entity& entity)
    {
        m_entities.erase(entity.id());
    }

    void EntityManager::destroy(const EntityId entityId)
    {
        m_entities.erase(entityId);
    }

    Entity& EntityManager::entity(const EntityId entityId)
    {
        /*
        const auto entity = std::find_if(m_entities.begin(), m_entities.end(), [&](const auto& lhs) {
            return lhs->id() == entityId;
        });
        return *entity->get();
        */
        auto& entity = m_entities.at(entityId);
        return *entity;
    }

    EntityId EntityManager::makeUniqueEntityId()
    {
        return lastEntityId++;
    }
}
} // end engine
