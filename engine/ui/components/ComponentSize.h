#pragma once

#include "ComponentSizeType.h"

#include <engine/common/Vector2D.h>

namespace engine {
namespace ui {
    class ComponentSize {
    public:
        ComponentSize(ComponentSizeType typeX, ComponentSizeType typeY, common::Vector2D<double> relativeSize)
            : m_typeX{ typeX }
            , m_typeY{ typeY }
            , m_relativeRatio{ relativeSize }
            , m_padding{}
            , m_marginStart{}
            , m_marginEnd{}
        {
        }
        ComponentSize(ComponentSizeType typeX, ComponentSizeType typeY)
            : ComponentSize(typeX, typeY, common::Vector2D<double>(1, 1))
        {
        }
        void setMarginEnd(const common::Vector2D<int> margin) { m_marginEnd = margin; }
        common::Vector2D<int> getMarginEnd() const { return m_marginEnd; }
        void setMarginStart(const common::Vector2D<int> margin) { m_marginStart = margin; }
        common::Vector2D<int> getMarginStart() const { return m_marginStart; }
        common::Vector2D<int> getPadding() const { return m_padding; }
        common::Vector2D<double> getRelativeRatio() const { return m_relativeRatio; }

        common::Vector2D<int> getSize(common::Vector2D<int> requiredSize,
            common::Vector2D<int> availableSize) const;

    private:
        ComponentSizeType m_typeX;
        ComponentSizeType m_typeY;
        common::Vector2D<double> m_relativeRatio;
        common::Vector2D<int> m_padding;
        common::Vector2D<int> m_marginStart;
        common::Vector2D<int> m_marginEnd;
    };
}
}