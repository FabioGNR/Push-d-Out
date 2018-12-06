#include "LineShape.h"
#include <graphics/IRenderVisitor.h>
#include <graphics/IRenderer.h>

namespace engine {
LineShape::LineShape(common::Vector2D<int> pos1, common::Vector2D<int> pos2, const Color& color)
    : m_position1(pos1)
    , m_position2(pos2)
    , m_color(color)
{
}

void LineShape::accept(const IRenderVisitor& visitor) const
{
    visitor.visit(*this);
}

const common::Vector2D<int>& LineShape::position1() const
{
    return m_position1;
}

const common::Vector2D<int>& LineShape::position2() const
{
    return m_position2;
}

const Color& LineShape::color() const
{
    return m_color;
}

void LineShape::draw(const IRenderer& renderer) const
{
    renderer.draw(*this);
}
const common::Vector2D<int>& LineShape::position() const
{
    return position1();
}
void LineShape::setPosition(const common::Vector2D<int>& position)
{
    m_position1 = position;
}
} // end namespace engine