#pragma once

#include <cassert>
#include <memory>
#include <unordered_map>

#include "Entity.h"

namespace engine {

class EntityManager {
    std::unordered_map<EntityId, std::unique_ptr<Entity>> m_entities;
    //std::vector<std::unique_ptr<Entity>> m_entities;
    EntityId lastEntityId = 0;

public:
    EntityManager() = default;
    Entity& create();
    Entity& entity(EntityId entityId);
    void destroy(const Entity& entity);
    void destroy(EntityId entityId);

private:
    EntityId makeUniqueEntityId();
};

} // end namespace engine
