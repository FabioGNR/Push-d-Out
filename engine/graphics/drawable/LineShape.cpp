#include "LineShape.h"
#include <graphics/IRenderVisitor.h>

namespace engine {
LineShape::LineShape(int x1, int x2, int y1, int y2)
    : m_x1(x1)
    , m_x2(x2)
    , m_y1(y1)
    , m_y2(y2)
{
}

void LineShape::accept(IRenderVisitor& visitor) const
{
    visitor.visit(*this);
}

int LineShape::x1() const
{
    return m_x1;
}

int LineShape::x2() const
{
    return m_x2;
}

int LineShape::y1() const
{
    return m_y1;
}

int LineShape::y2() const
{
    return m_y2;
}
} // end namespace engine