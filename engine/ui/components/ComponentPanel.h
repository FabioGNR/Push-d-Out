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
        virtual size_t countNavigatableChildren() const = 0;
        virtual Component* getNavigatableAt(size_t index) const = 0;

    protected:
        FlowDirection m_flowDirection;
    };
}
}