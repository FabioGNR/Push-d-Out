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
        WrappedComponent(std::shared_ptr<Component> component, LayoutAnchor anchor)
            : m_anchor{ anchor }
            , m_component{ std::move(component) }
        {
        }
        DrawContext draw(DrawContext context) const { return m_component->draw(std::move(context)); };
        std::shared_ptr<Component> getComponent() const { return m_component; }
        LayoutAnchor getAnchor() const { return m_anchor; }

    private:
        LayoutAnchor m_anchor;
        std::shared_ptr<Component> m_component;
    };
}
}