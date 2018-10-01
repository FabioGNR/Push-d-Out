#include "Entity.h"

namespace engine {

Entity::Entity(const EntityId id)
    : m_id(id)
{
}

EntityId Entity::id() const
{
    return m_id;
}

} // end namespace engine
