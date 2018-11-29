#include "LayoutPanel.h"
#include <algorithm>

namespace engine {
namespace ui {
    void LayoutPanel::addComponent(std::unique_ptr<Component> component, LayoutAnchor anchor)
    {
        WrappedComponent wrappedComponent{ std::move(component), anchor };
        m_components.insert(std::move(wrappedComponent));
    }

    DrawContext LayoutPanel::draw(DrawContext context)
    {
        DrawContext compositeContext{ context };
        DrawContext childContext{ context };
        childContext.availableSize = (context.availableSize / sumRelativeSize()).castTo<int>();
        for (const auto& component : m_components) {
            const auto childPosition = getChildPosition(context.renderer,
                component,
                childContext.availableSize,
                context.availableSize);

            childContext.pos = context.pos + childPosition;
            DrawContext updatedContext = component.draw(childContext);
            compositeContext.pos = common::Vector2D<int>::max(compositeContext.pos, updatedContext.pos);
        }
        return compositeContext;
    }

    common::Vector2D<int> LayoutPanel::calculateSize(const IRenderer& renderer, common::Vector2D<int> availableSize) const
    {
        common::Vector2D<int> requiredSize{ 0, 0 };
        const auto availableChildSize = (availableSize / sumRelativeSize().castTo<int>()).castTo<int>();

        for (const auto& component : m_components) {
            const auto componentSize = component.getComponent().calculateSize(renderer,
                availableChildSize);
            if (m_flowDirection == FlowDirection::Horizontal) {
                requiredSize.x += componentSize.x;
                requiredSize.y = std::max(requiredSize.y, componentSize.y);
            } else {
                requiredSize.y += componentSize.y;
                requiredSize.x = std::max(requiredSize.x, componentSize.x);
            }
        }
        return m_size.getSize(requiredSize, availableSize);
    }

    common::Vector2D<double> LayoutPanel::sumRelativeSize() const
    {
        common::Vector2D<int> minimumSize{ 1, 1 };
        common::Vector2D<double> sum{ 1, 1 };
        for (const auto& component : m_components) {
            sum += component.getComponent().getSize().getRelativeRatio();
        }
        if (m_flowDirection == FlowDirection::Vertical) {
            sum.x = 1;
        } else {
            sum.y = 1;
        }
        return common::Vector2D<double>::max(sum, minimumSize.castTo<double>());
    }

    common::Vector2D<int> LayoutPanel::getChildPosition(const IRenderer& renderer,
        const WrappedComponent& component,
        common::Vector2D<int> availableSize,
        common::Vector2D<int> parentSize) const
    {
        common::Vector2D<int> position{ 0, 0 };
        const auto calculatedSize = component.getComponent().calculateSize(renderer, availableSize);

        switch (component.getAnchor()) {
        case LayoutAnchor::Start:
            break;
        case LayoutAnchor::End:
            position = parallelWithDirection(parentSize - calculatedSize);
            break;
        case LayoutAnchor::Center:
            position = parallelWithDirection((parentSize - calculatedSize) / 2);
            break;
        }
        return position;
    }

    Component* LayoutPanel::getNavigatableAt(size_t index) const
    {
        size_t currentTotal = 0;
        for (const auto& wrapper : m_components) {
            const auto* panel = dynamic_cast<ComponentPanel*>(&(wrapper.getComponent()));
            if (panel != nullptr) {
                size_t childTotal = panel->countNavigatableChildren();
                if (currentTotal + childTotal > index) {
                    return panel->getNavigatableAt(index - currentTotal);
                }
                currentTotal += childTotal;
            } else if (wrapper.getComponent().isNavigatable()) {
                currentTotal++;
                if (currentTotal > index) {
                    return &(wrapper.getComponent());
                }
            }
        }
        return nullptr;
    }

    size_t LayoutPanel::countNavigatableChildren() const
    {
        size_t total = 0;
        for (const auto& wrapper : m_components) {
            const auto* panel = dynamic_cast<ComponentPanel*>(&(wrapper.getComponent()));
            if (panel != nullptr) {
                total += panel->countNavigatableChildren();
            } else if (wrapper.getComponent().isNavigatable()) {
                total++;
            }
        }
        return total;
    }
}
}