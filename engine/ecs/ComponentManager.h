#pragma once

#include "Component.h"
#include "Entity.h"

#include <cassert>
#include <memory>
#include <type_traits>
#include <unordered_map>
#include <utility>

namespace engine {
namespace ecs {
    class IComponentManager {
    public:
        IComponentManager();
        virtual ~IComponentManager();
        virtual void remove(EntityId entity) = 0;
        virtual void remove(Entity& entity) = 0;
    };

    using ComponentMap = std::unordered_map<EntityId, std::unique_ptr<IComponent>>;
    template <typename Component>
    class BaseComponentManager : public IComponentManager {
        ComponentMap m_components;

    public:
        template <typename... ComponentArgs>
        Component& add(Entity& entity, ComponentArgs&&... args)
        {
            static_assert(std::is_base_of<IComponent, Component>::value,
                "Component must be inherited from BaseComponent");

            auto component = std::make_unique<Component>(std::forward<ComponentArgs>(args)...);
            auto* componentPtr = component.get();

            // TODO: Check if component insertion was valid
            m_components.insert({ entity.id(), std::move(component) });

            entity.registerComponent<Component>();
            return *componentPtr;
        }

        void remove(const EntityId entity) override
        {
            m_components.erase(entity);
        }

        void remove(Entity& entity) override
        {
            m_components.erase(entity.id());
        }

        Component& get(const EntityId entityId) const
        {
            return *reinterpret_cast<Component*>(m_components.at(entityId).get());
        }

        Component& get(const Entity& entity) const
        {
            return get(entity.id());
        }

        ComponentMap& getAll()
        {
            return m_components;
        }
    };

    using ManagerMap = std::unordered_map<engine::ecs::ComponentId, std::unique_ptr<IComponentManager>>;
    class ComponentManager {
        ManagerMap m_managers;

    public:
        template <typename Component>
        void addManager()
        {
            static_assert(std::is_base_of<IComponent, Component>::value,
                "Component must be inherited from BaseComponent");

            m_managers.insert({ Component::familyId(),
                std::make_unique<BaseComponentManager<Component>>() });
        }

        template <typename Component>
        BaseComponentManager<Component>& getManager()
        {
            static_assert(std::is_base_of<IComponent, Component>::value,
                "Component must be inherited from BaseComponent");

            auto familyId = Component::familyId();
            bool found = m_managers.count(familyId) != 0;

            if (!found) {
                addManager<Component>();
                familyId = Component::familyId();
            }

            auto& manager = m_managers.at(familyId);
            return *reinterpret_cast<BaseComponentManager<Component>*>(manager.get());
        }

        template <typename Component>
        Component& get(const EntityId entityId) const
        {
            return getManager<Component>().get(entityId);
        }

        template <typename Component>
        Component& get(const Entity& entity) const
        {
            return getManager<Component>().get(entity);
        }

        ManagerMap& getAll()
        {
            return m_managers;
        }

        template <typename Component, typename... ComponentArgs>
        Component& add(Entity& entity, ComponentArgs&&... args)
        {
            static_assert(std::is_base_of<IComponent, Component>::value,
                "Component must be inherited from BaseComponent");

            auto& manager = getManager<Component>();
            return manager.add(entity, std::forward<ComponentArgs>(args)...);
        }

        template <typename Component>
        void remove(Entity& entity)
        {
            getManager<Component>().remove(entity);
        }

        template <typename Component>
        void remove(const EntityId entity)
        {
            getManager<Component>().remove(entity);
        }
    };
}
} // end namespace engine
