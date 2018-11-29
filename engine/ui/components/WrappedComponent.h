#include <utility>

#include <utility>

#pragma once
#include "Component.h"
#include "FlowDirection.h"
#include "LayoutAnchor.h"
#include <memory>

namespace engine {
namespace ui {
    class WrappedComponent {
    public:
        WrappedComponent(std::unique_ptr<Component> component, LayoutAnchor anchor)
            : m_anchor{ anchor }
            , m_component{ std::move(component) }
        {
        }
        DrawContext draw(DrawContext context) const { return m_component->draw(context); };
        Component& getComponent() const { return *m_component; }
        LayoutAnchor getAnchor() const { return m_anchor; }

        WrappedComponent(const WrappedComponent& other) = delete;
        WrappedComponent(WrappedComponent&& other)
        {
            this->m_component = std::move(other.m_component);
            this->m_anchor = other.m_anchor;
        }

        WrappedComponent& operator=(const WrappedComponent& other) = delete;
        WrappedComponent& operator=(WrappedComponent&& other)
        {
            if (this != &other) {
                this->m_component = std::move(other.m_component);
                this->m_anchor = other.m_anchor;
            }
            return *this;
        }

    private:
        LayoutAnchor m_anchor;
        std::unique_ptr<Component> m_component;
    };
}
}