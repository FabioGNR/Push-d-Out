#pragma once

#include "Component.h"
#include "Entity.h"

#include <cassert>
#include <memory>
#include <type_traits>
#include <unordered_map>
#include <utility>

namespace engine {

class IComponentManager {
public:
    IComponentManager();
    virtual ~IComponentManager();
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

        // FIXME: Check if insertion was validC
        m_components.insert({ entity.id(), std::move(component) });

        entity.registerComponent<Component>();
        return *componentPtr;
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

using ManagerMap = std::unordered_map<engine::ComponentId, std::unique_ptr<IComponentManager>>;
class ComponentManager : public IComponentManager {
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

        //auto& managerUptr = m_managers.at(Component::familyId());
        return *reinterpret_cast<BaseComponentManager<Component>*>(m_managers.at(Component::familyId()).get());
    }

    template <typename Component, typename... ComponentArgs>
    Component& add(Entity& entity, ComponentArgs&&... args)
    {
        static_assert(std::is_base_of<IComponent, Component>::value,
            "Component must be inherited from BaseComponent");

        return getManager<Component>().add(entity, std::forward<ComponentArgs>(args)...);
    }
};

} // end namespace engine
