#pragma once
#include "ComponentPanel.h"
#include "FlowDirection.h"
#include "WrappedComponent.h"
#include <memory>
#include <vector>

namespace engine {
namespace ui {
    class StackPanel : public ComponentPanel {
    public:
        StackPanel(ComponentSize size, FlowDirection flowDirection)
            : ComponentPanel(size, flowDirection)
        {
        }

        ~StackPanel() override = default;

        common::Vector2D<int> calculateSize(const IRenderer& renderer, common::Vector2D<int> availableSize) const override;

        common::Vector2D<double> sumRelativeSize() const;

        DrawContext draw(DrawContext context) override;

        void addComponent(std::unique_ptr<Component> component);

        size_t countNavigatableChildren() const override;

        Component* getNavigatableAt(size_t index) const override;

    private:
        std::vector<std::unique_ptr<Component>> m_components;

        common::Vector2D<int> getRequiredSize(const IRenderer& renderer, common::Vector2D<int> availableChildSize) const;
    };
}
}