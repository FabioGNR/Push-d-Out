#pragma once
#include "Component.h"
#include "ComponentPanel.h"
#include "FlowDirection.h"
#include "LayoutAnchor.h"
#include "WrappedComponent.h"
#include <memory>
#include <set>

namespace engine {
namespace ui {

    class LayoutPanel : public ComponentPanel {
    public:
        LayoutPanel(ComponentSize size, FlowDirection flowDirection)
            : ComponentPanel(size, flowDirection)
        {
        }

        ~LayoutPanel() override = default;

        common::Vector2D<int> calculateSize(const IRenderer& renderer, common::Vector2D<int> availableSize) const override;

        common::Vector2D<double> sumRelativeSize() const;

        DrawContext draw(DrawContext context) override;

        void addComponent(std::unique_ptr<Component> component, LayoutAnchor anchor);

        size_t countNavigatableChildren() const override;

        Component* getNavigatableAt(size_t index) const override;
        struct sortByAnchor {
            bool operator()(const WrappedComponent& a, const WrappedComponent& b) const
            {
                return a.getAnchor() < b.getAnchor();
            }
        };

    private:
        std::set<WrappedComponent, sortByAnchor> m_components;
        common::Vector2D<int> getChildPosition(
            const IRenderer& renderer,
            const WrappedComponent& component,
            common::Vector2D<int> availableSize,
            common::Vector2D<int> parentSize) const;
    };
}
}