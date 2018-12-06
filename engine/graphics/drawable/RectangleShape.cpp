#include "RectangleShape.h"
#include "graphics/IRenderVisitor.h"
#include "graphics/IRenderer.h"

namespace engine {
RectangleShape::RectangleShape(common::Vector2D<int> position, common::Vector2D<int> size, const Color& color, bool fill)
    : m_position(position)
    , m_size(size)
    , m_fill(fill)
    , m_color(color)
{
}

void RectangleShape::accept(const IRenderVisitor& visitor) const
{
    visitor.visit(*this);
}

const Color& RectangleShape::color() const
{
    return m_color;
}

const common::Vector2D<int>& RectangleShape::size() const
{
    return m_size;
}

const common::Vector2D<int>& RectangleShape::position() const
{
    return m_position;
}

void RectangleShape::setColor(const Color& color)
{
    m_color = color;
}

void RectangleShape::setSize(const common::Vector2D<int>& size)
{
    m_size = size;
}

void RectangleShape::setPosition(const common::Vector2D<int>& position)
{
    m_position = position;
}
bool RectangleShape::isFilled() const
{
    return m_fill;
}
void RectangleShape::setFill(bool fill)
{
    m_fill = fill;
}

void RectangleShape::draw(const IRenderer& renderer) const
{
    renderer.draw(*this);
}

} // end namespace engine
