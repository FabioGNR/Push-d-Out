#include "StackPanel.h"

namespace engine {
namespace ui {
    void StackPanel::addComponent(const std::shared_ptr<Component>& component)
    {
        m_components.push_back(component);
    }

    DrawContext StackPanel::draw(DrawContext context)
    {

        DrawContext childContext{ context };
        childContext.availableSize = (context.availableSize / sumRelativeSize()).castTo<int>();

        for (const auto& component : m_components) {
            DrawContext updatedContext = component->draw(childContext);
            if (m_flowDirection == FlowDirection::Horizontal) {
                childContext.pos.x = updatedContext.pos.x;
            } else {
                childContext.pos.y = updatedContext.pos.y;
            }
            childContext.pos += component->getSize().getMargin();
        }
        return context;
    }

    common::Vector2D<int> StackPanel::calculateSize(common::Vector2D<int> availableSize) const
    {
        common::Vector2D<int> requiredSize{ 0, 0 };
        common::Vector2D<int> availableChildSize = (availableSize / sumRelativeSize()).castTo<int>();

        for (const auto& component : m_components) {
            common::Vector2D<int> componentSize = component->calculateSize(availableChildSize);
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

    common::Vector2D<double> StackPanel::sumRelativeSize() const
    {
        common::Vector2D<int> minimumSize{ 1, 1 };
        common::Vector2D<double> sum{ 0, 0 };
        for (const auto& component : m_components) {
            sum += component->getSize().getRelativeRatio();
        }
        if (m_flowDirection == FlowDirection::Vertical) {
            sum.x = 1;
        } else {
            sum.y = 1;
        }
        return common::Vector2D<double>::max(sum, minimumSize.castTo<double>());
    }

    std::shared_ptr<Component> StackPanel::getNavigatableAt(size_t index) const
    {
        size_t currentTotal = 0;
        for (const auto& component : m_components) {
            auto* panel = dynamic_cast<ComponentPanel*>(component.get());
            if (panel != nullptr) {
                size_t childTotal = panel->countNavigatableChildren();
                if (currentTotal + childTotal > index) {
                    return panel->getNavigatableAt(index - currentTotal);
                }
                currentTotal += childTotal;
            } else if (component->isNavigatable()) {
                currentTotal++;
                if (currentTotal > index) {
                    return component;
                }
            }
        }
        return nullptr;
    }

    size_t StackPanel::countNavigatableChildren() const
    {
        size_t total = 0;
        for (const auto& component : m_components) {
            auto* panel = dynamic_cast<ComponentPanel*>(component.get());
            if (panel != nullptr) {
                total += panel->countNavigatableChildren();
            } else if (component->isNavigatable()) {
                total++;
            }
        }
        return total;
    }
}
}