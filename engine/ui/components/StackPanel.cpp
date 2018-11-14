#include "StackPanel.h"

namespace engine {
namespace ui {
    void StackPanel::addComponent(std::unique_ptr<Component> component)
    {
        m_components.push_back(std::move(component));
    }

    DrawContext StackPanel::draw(DrawContext context)
    {
        DrawContext childrenContext{ context };
        childrenContext.availableSize = (context.availableSize / sumRelativeSize()).castTo<int>();
        auto requiredSize = getRequiredSize(context.renderer, childrenContext.availableSize);

        for (const auto& component : m_components) {
            DrawContext componentContext{ childrenContext };
            // center component in cross axis
            auto childSize = component->calculateSize(context.renderer, childrenContext.availableSize);
            if (m_flowDirection == FlowDirection::Horizontal) {
                componentContext.pos.y = componentContext.pos.y + (requiredSize.y - childSize.y) / 2;
            } else {
                componentContext.pos.x = componentContext.pos.x + (requiredSize.x - childSize.x) / 2;
            }
            // draw component
            DrawContext updatedContext = component->draw(componentContext);
            // update position for next component
            if (m_flowDirection == FlowDirection::Horizontal) {
                childrenContext.pos.x = updatedContext.pos.x;
            } else {
                childrenContext.pos.y = updatedContext.pos.y;
            }
            childrenContext.pos += component->getSize().getMargin();
        }
        return context;
    }

    common::Vector2D<int> StackPanel::calculateSize(const IRenderer& renderer, common::Vector2D<int> availableSize) const
    {
        common::Vector2D<int> availableChildSize = (availableSize / sumRelativeSize()).castTo<int>();

        auto requiredSize = getRequiredSize(renderer, availableChildSize);
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

    Component* StackPanel::getNavigatableAt(size_t index) const
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
                    return component.get();
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

    common::Vector2D<int> StackPanel::getRequiredSize(const IRenderer& renderer, common::Vector2D<int> availableChildSize) const
    {
        common::Vector2D<int> requiredSize{ 0, 0 };

        for (const auto& component : m_components) {
            common::Vector2D<int> componentSize = component->calculateSize(renderer, availableChildSize);
            if (m_flowDirection == FlowDirection::Horizontal) {
                requiredSize.x += componentSize.x;
                requiredSize.y = std::max(requiredSize.y, componentSize.y);
            } else {
                requiredSize.y += componentSize.y;
                requiredSize.x = std::max(requiredSize.x, componentSize.x);
            }
        }
        return requiredSize;
    }
}
}