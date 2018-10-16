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

        bool hasItem() const
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

    private:
        engine::ecs::Entity* m_entity;
    };
}
}