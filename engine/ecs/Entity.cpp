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
}
} // end namespace engine
