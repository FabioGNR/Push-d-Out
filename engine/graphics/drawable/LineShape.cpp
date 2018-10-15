#include "LineShape.h"
#include <graphics/IRenderVisitor.h>

namespace engine {
LineShape::LineShape(common::Vector2D<int> pos1, common::Vector2D<int> pos2)
    : m_position1(pos1)
    , m_position2(pos2)
{
}

void LineShape::accept(IRenderVisitor& visitor) const
{
    visitor.visit(*this);
}

common::Vector2D<int> LineShape::position1() const
{
    return m_position1;
}
common::Vector2D<int> LineShape::position2() const
{
    return m_position2;
}
} // end namespace engine