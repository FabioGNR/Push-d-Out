#ifndef SDL_GAME_WORLD_H
#define SDL_GAME_WORLD_H

#include "Component.h"
#include "ComponentManager.h"
#include "Entity.h"
#include "EntityManager.h"

#include <algorithm>
#include <functional>
#include <vector>

namespace engine {

class World {
    EntityManager& m_entityManager;
    ComponentManager& m_componentManager;

public:
    World(EntityManager& entityManager, ComponentManager& componentManager)
        : m_entityManager(entityManager)
        , m_componentManager(componentManager)
    {
    }

    template <typename... Components>
    void forEachEntityWith(std::function<void(Entity&)>&& func)
    {
        const std::vector<std::reference_wrapper<ComponentMap>> componentMaps = {
            m_componentManager.getManager<Components>().getAll()...
        };

        const auto& smallestMapRef = *std::min_element(componentMaps.cbegin(), componentMaps.cend(),
            [](const auto& lhs, const auto& rhs) {
                return lhs.get().size() < rhs.get().size();
            });

        for (auto& entityIterator : smallestMapRef.get()) {
            auto& entity = m_entityManager.entity(entityIterator.first);
            if (entityHasComponents<Components...>(entity)) {
                func(entity);
            }
        }
    }

private:
    template <typename... Components>
    inline bool entityHasComponents(const Entity& entity) const
    {
        return entity.hasComponent<Components...>();
    }
};

} // end namespace engine

#endif // SDL_GAME_WORLD_H
