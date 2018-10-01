#include "RectangleShape.h"
#include "graphics/IRenderVisitor.h"

namespace engine {
void RectangleShape::accept(IRenderVisitor& visitor) const
{
    visitor.visit(*this);
}

int RectangleShape::width() const
{
    return m_width;
}

int RectangleShape::height() const
{
    return m_height;
}

int RectangleShape::x() const
{
    return m_x;
}

int RectangleShape::y() const
{
    return m_y;
}

RectangleShape::RectangleShape(int x, int y, int width, int height, const Color& color)
    : m_width(width)
    , m_height(height)
    , m_x(x)
    , m_y(y)
    , m_color(color)
{
}

void RectangleShape::setWidth(int width)
{
    m_width = width;
}

void RectangleShape::setHeight(int height)
{
    m_height = height;
}

void RectangleShape::setX(int x)
{
    m_x = x;
}

void RectangleShape::setY(int y)
{
    m_y = y;
}

const Color& RectangleShape::color() const
{
    return m_color;
}
} // end namespace engine
