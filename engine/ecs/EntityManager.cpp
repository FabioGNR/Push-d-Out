#include "EntityManager.h"

#include "engine/exceptions/EntityNotFoundException.h"
#include <algorithm>
#include <utility>

namespace engine {
namespace ecs {
    Entity& EntityManager::create()
    {
        auto entity = std::make_unique<Entity>(makeUniqueEntityId());
        auto* entityPtr = entity.get();
        m_entities.insert(std::make_pair(entityPtr->id(), std::move(entity)));

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
        auto it = m_entities.find(entityId);
        if (it != m_entities.end()) {
            return *(it->second);
        }
        throw engine::exceptions::EntityNotFoundException();
    }

    EntityId EntityManager::makeUniqueEntityId()
    {
        return lastEntityId++;
    }

    std::size_t EntityManager::count() const
    {
        return m_entities.size();
    }
}
} // end engine
