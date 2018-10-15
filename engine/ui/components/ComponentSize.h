#pragma once
#include "ComponentSizeType.h"
#include <common/Vector2D.h>

namespace engine {
namespace ui {
    class ComponentSize {
    public:
        ComponentSize(ComponentSizeType typeX, ComponentSizeType typeY, common::Vector2D relativeSize)
            : m_typeX{ typeX }
            , m_typeY{ typeY }
            , m_relativeRatio{ relativeSize }
            , m_padding{ 0, 0 }
            , m_margin{ 0, 0 }
        {
        }
        ComponentSize(ComponentSizeType typeX, ComponentSizeType typeY)
            : ComponentSize(typeX, typeY, common::Vector2D(1, 1))
        {
        }
        void setMargin(const common::Vector2D margin) { m_margin = margin; }
        common::Vector2D getMargin() const { return m_margin; }
        common::Vector2D getPadding() const { return m_padding; }
        common::Vector2D getRelativeRatio() const { return m_relativeRatio; }

        common::Vector2D getSize(common::Vector2D requiredSize,
            common::Vector2D availableSize) const;

    private:
        ComponentSizeType m_typeX;
        ComponentSizeType m_typeY;
        common::Vector2D m_relativeRatio;
        common::Vector2D m_padding;
        common::Vector2D m_margin;
    };
}
}