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
        const auto requiredSize = getRequiredSize(context.renderer, childrenContext.availableSize);

        for (const auto& component : m_components) {
            DrawContext componentContext{ childrenContext };
            // center component in cross axis
            const auto childSize = component->calculateSize(context.renderer, childrenContext.availableSize);
            componentContext.pos += perpendicularWithDirection((requiredSize - childSize) / 2);
            // draw component
            DrawContext updatedContext = component->draw(componentContext);
            // update position for next component
            childrenContext.pos = parallelWithDirection(updatedContext.pos) + perpendicularWithDirection(context.pos);
            childrenContext.pos += parallelWithDirection(component->getSize().getMargin());
        }
        return context;
    }

    common::Vector2D<int> StackPanel::calculateSize(const IRenderer& renderer, common::Vector2D<int> availableSize) const
    {
        const auto availableChildSize = (availableSize / sumRelativeSize()).castTo<int>();
        const auto requiredSize = getRequiredSize(renderer, availableChildSize);
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
            const auto* panel = dynamic_cast<ComponentPanel*>(component.get());
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
            const auto* panel = dynamic_cast<ComponentPanel*>(component.get());
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
            const auto componentSize = component->calculateSize(renderer, availableChildSize);
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