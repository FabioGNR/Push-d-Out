#pragma once
#include "ComponentSize.h"
#include "common/Vector2D.h"
#include "ui/DrawContext.h"
#include <memory>

namespace engine {
namespace ui {
    class Component {
    public:
        explicit Component(ComponentSize size)
            : m_size{ size }
        {
        }
        virtual DrawContext draw(DrawContext context) = 0;
        virtual void processInputEvent() {}
        virtual common::Vector2D<int> calculateSize(common::Vector2D<int> availableSize) const = 0;
        ComponentSize getSize() { return m_size; }
        virtual bool isNavigatable() { return false; }

    protected:
        ComponentSize m_size;
    };
}
}