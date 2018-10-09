#pragma once

#include "Component.h"
#include "ComponentManager.h"
#include "Entity.h"
#include "EntityManager.h"
#include "System.h"
#include "SystemManager.h"
#include "definitions/SystemPriority.h"

#include <algorithm>
#include <functional>
#include <vector>

namespace engine {
namespace ecs {
    class World {
    private:
        EntityManager m_entityManager;
        ComponentManager m_componentManager;
        SystemManager m_systemManager;

    public:
        World() = default;
        virtual ~World() = default;

        Entity& createEntity();

        void destroyEntity(Entity& entity);

        template <typename Component>
        Component& getComponent(const Entity& entity) const
        {
            return m_componentManager.getManager<Component>().get(entity);
        }

        template <typename Component, typename... ComponentArgs>
        Component& addComponent(Entity& entity, ComponentArgs&&... args)
        {
            static_assert(std::is_base_of<IComponent, Component>::value,
                "Component must be inherited from BaseComponent");
            entity.registerComponent<Component>();
            return m_componentManager.getManager<Component>().add(entity, std::forward<ComponentArgs>(args)...);
        }

        template <typename Component>
        void removeComponent(Entity& entity)
        {
            static_assert(std::is_base_of<IComponent, Component>::value,
                "Component must be inherited from BaseComponent");

            m_componentManager.remove<Component>(entity);
            entity.unregisterComponent<Component>();
        }

        template <typename... Components>
        void forEachEntityWith(std::function<void(Entity&)>&& func)
        {
            const std::vector<std::reference_wrapper<ComponentMap>> componentMaps = {
                m_componentManager.getManager<Components>()->getAll()...
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

        template <typename Component>
        void addComponentManager()
        {
            m_componentManager.addManager<Component>();
        }

        template <typename System, typename... SystemArgs>
        void addSystem(definitions::SystemPriority priority, SystemArgs&&... args)
        {
            m_systemManager.add<System>(priority, args...);
        }

    private:
        template <typename... Components>
        inline bool entityHasComponents(const Entity& entity) const
        {
            return entity.hasComponent<Components...>();
        }
    };
} // end namespace ecs
} // end namespace engine
