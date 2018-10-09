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

        common::Vector2D calculateSize(common::Vector2D availableSize) const override;

        common::Vector2D sumRelativeSize() const;

        DrawContext draw(DrawContext context) override;

        void addComponent(const std::shared_ptr<Component>& component);

        size_t countNavigatableChildren() const override;

        std::shared_ptr<Component> getNavigatableAt(size_t index) const override;

    private:
        std::vector<std::shared_ptr<Component>> m_components;
    };
}
}