#pragma once

#include "Component.h"
#include "FlowDirection.h"
namespace engine {
namespace ui {
    class ComponentPanel : public Component {
    public:
        explicit ComponentPanel(ComponentSize size, FlowDirection flowDirection)
            : Component(size)
            , m_flowDirection{ flowDirection }
        {
        }
        ~ComponentPanel() override = default;

        virtual size_t countNavigatableChildren() const = 0;
        virtual Component* getNavigatableAt(size_t index) const = 0;

    protected:
        FlowDirection m_flowDirection;
        common::Vector2D<int> parallelWithDirection(const common::Vector2D<int>& in) const
        {
            if (m_flowDirection == FlowDirection::Vertical) {
                return { 0, in.y };
            } else {
                return { in.x, 0 };
            }
        }
        common::Vector2D<int> perpendicularWithDirection(const common::Vector2D<int>& in) const
        {
            if (m_flowDirection != FlowDirection::Vertical) {
                return { 0, in.y };
            } else {
                return { in.x, 0 };
            }
        }
    };
}
}