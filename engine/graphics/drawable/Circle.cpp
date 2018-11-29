#include "Circle.h"
#include "graphics/IRenderVisitor.h"

namespace engine {
Circle::Circle(common::Vector2D<double> center, double radius, const Color& color, bool fill)
    : m_center(center)
    , m_radius(radius)
    , m_fill(fill)
    , m_color(color)
{
}

void Circle::accept(IRenderVisitor& visitor) const
{
    visitor.visit(*this);
}

double Circle::radius() const
{
    return m_radius;
}

const common::Vector2D<double> Circle::center() const
{
    return m_center;
}

void Circle::radius(double radius)
{
    m_radius = radius;
}

void Circle::center(common::Vector2D<double> center)
{
    m_center = center;
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
} // end namespace engine
