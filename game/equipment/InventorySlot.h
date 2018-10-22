#pragma once
#include <engine/ecs/Entity.h>

namespace game {
namespace equipment {
    class InventorySlot {
    public:
        InventorySlot()
        {
            clear();
        }

        bool hasValue() const
        {
            return m_entity != nullptr;
        }

        void set(engine::ecs::Entity* entity)
        {
            m_entity = entity;
        }

        void clear()
        {
            m_entity = nullptr;
        }

        engine::ecs::Entity& get() const {
            return *m_entity;
        }

    private:
        engine::ecs::Entity* m_entity;
    };
}
}