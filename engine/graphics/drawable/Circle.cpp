#include "Circle.h"
#include "graphics/IRenderVisitor.h"
#include "graphics/IRenderer.h"

namespace engine {
Circle::Circle(common::Vector2D<double> center, double radius, const Color& color, bool fill)
    : m_center(center)
    , m_radius(radius)
    , m_fill(fill)
    , m_color(color)
{
}

void Circle::accept(const IRenderVisitor& visitor) const
{
    visitor.visit(*this);
}

double Circle::radius() const
{
    return m_radius;
}

void Circle::radius(double radius)
{
    m_radius = radius;
}

void Circle::fill(bool fill)
{
    m_fill = fill;
}

bool Circle::fill() const
{
    return m_fill;
}

const Color& Circle::color() const
{
    return m_color;
}

void Circle::draw(const IRenderer& renderer) const
{
    renderer.draw(*this);
}
const common::Vector2D<int>& Circle::position() const
{
    static auto centerInInt = common::Vector2D<int>{ 0, 0 };
    centerInInt = m_center.castTo<int>();
    return centerInInt;
}

void Circle::setPosition(const common::Vector2D<int>& position)
{
    m_center = position.castTo<double>();
}
} // end namespace engine
