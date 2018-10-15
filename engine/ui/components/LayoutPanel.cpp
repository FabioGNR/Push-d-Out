#include "LayoutPanel.h"
#include <algorithm>

namespace engine {
namespace ui {
    void LayoutPanel::addComponent(const std::shared_ptr<Component>& component, LayoutAnchor anchor)
    {
        std::shared_ptr<WrappedComponent> wrappedComponent = std::make_shared<WrappedComponent>(component, anchor);
        m_components.insert(wrappedComponent);
    }

    DrawContext LayoutPanel::draw(DrawContext context)
    {
        DrawContext compositeContext{ context };
        DrawContext childContext{ context };
        childContext.availableSize = context.availableSize / sumRelativeSize();
        for (const auto& component : m_components) {
            common::Vector2D childPosition = getChildPosition(component,
                childContext.availableSize,
                context.availableSize);

            childContext.pos = childPosition + context.pos;
            DrawContext updatedContext = component->draw(childContext);
            compositeContext.pos = compositeContext.pos.max(updatedContext.pos);
        }
        return compositeContext;
    }

    common::Vector2D LayoutPanel::calculateSize(common::Vector2D availableSize) const
    {
        common::Vector2D requiredSize{ 0, 0 };
        common::Vector2D availableChildSize = availableSize / sumRelativeSize();

        for (const auto& component : m_components) {
            common::Vector2D componentSize = component->getComponent()->calculateSize(availableChildSize);
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

    common::Vector2D LayoutPanel::sumRelativeSize() const
    {
        common::Vector2D minimumSize{ 1, 1 };
        common::Vector2D sum{ 1, 1 };
        for (const auto& component : m_components) {
            sum += component->getComponent()->getSize().getRelativeRatio();
        }
        if (m_flowDirection == FlowDirection::Vertical) {
            sum.x = 1;
        } else {
            sum.y = 1;
        }
        return sum.max(minimumSize);
    }

    common::Vector2D LayoutPanel::getChildPosition(std::shared_ptr<WrappedComponent> component,
        common::Vector2D availableSize,
        common::Vector2D parentSize) const
    {
        common::Vector2D position{ 0, 0 };
        common::Vector2D calculatedSize = component->getComponent()->calculateSize(availableSize);

        switch (component->getAnchor()) {
        case LayoutAnchor::Start:
            break;
        case LayoutAnchor::End:
            if (m_flowDirection == FlowDirection::Horizontal) {
                position.x = parentSize.x - calculatedSize.x;
            } else {
                position.y = parentSize.y - calculatedSize.y;
            }
            break;
        case LayoutAnchor::Center:
            if (m_flowDirection == FlowDirection::Horizontal) {
                position.x = (parentSize.x - calculatedSize.x) / 2;
            } else {
                position.y = (parentSize.y - calculatedSize.y) / 2;
            }
            break;
        }
        return position;
    }

    std::shared_ptr<Component> LayoutPanel::getNavigatableAt(size_t index) const
    {
        size_t currentTotal = 0;
        for (const auto& wrapper : m_components) {
            auto* panel = dynamic_cast<ComponentPanel*>(wrapper->getComponent().get());
            if (panel != nullptr) {
                size_t childTotal = panel->countNavigatableChildren();
                if (currentTotal + childTotal > index) {
                    return panel->getNavigatableAt(index - currentTotal);
                }
                currentTotal += childTotal;
            } else if (wrapper->getComponent()->isNavigatable()) {
                currentTotal++;
                if (currentTotal > index) {
                    return wrapper->getComponent();
                }
            }
        }
        return nullptr;
    }

    size_t LayoutPanel::countNavigatableChildren() const
    {
        size_t total = 0;
        for (const auto& wrapper : m_components) {
            auto* panel = dynamic_cast<ComponentPanel*>(wrapper->getComponent().get());
            if (panel != nullptr) {
                total += panel->countNavigatableChildren();
            } else if (wrapper->getComponent()->isNavigatable()) {
                total++;
            }
        }
        return total;
    }
}
}