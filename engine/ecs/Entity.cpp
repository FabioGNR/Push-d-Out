#include "Entity.h"

namespace engine {
namespace ecs {
    Entity::Entity(const EntityId id)
        : m_id(id)
    {
    }

    EntityId Entity::id() const
    {
        return m_id;
    }

    bool Entity::operator<(const Entity& rhs) const
    {
        return m_id < rhs.m_id;
    }

    bool Entity::operator>(const Entity& rhs) const
    {
        return rhs < *this;
    }

    bool Entity::operator<=(const Entity& rhs) const
    {
        return !(rhs < *this);
    }

    bool Entity::operator>=(const Entity& rhs) const
    {
        return !(*this < rhs);
    }
}
} // end namespace engine
