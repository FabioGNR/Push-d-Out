#include "RectangleShape.h"
#include "graphics/IRenderVisitor.h"

namespace engine {
void RectangleShape::accept(IRenderVisitor& visitor) const
{
    visitor.visit(*this);
}

common::Vector2D RectangleShape::size() const
{
    return m_size;
}

common::Vector2D RectangleShape::position() const
{
    return m_position;
}

RectangleShape::RectangleShape(common::Vector2D position, common::Vector2D size, const Color& color)
    : m_position(position)
    , m_size(size)
    , m_color(color)
{
}

void RectangleShape::setSize(common::Vector2D size)
{
    m_size = size;
}

void RectangleShape::setPosition(common::Vector2D position)
{
    m_position = position;
}

const Color& RectangleShape::color() const
{
    return m_color;
}
} // end namespace engine
