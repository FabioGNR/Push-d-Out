#include "Surface.h"
#include "engine/graphics/IRenderVisitor.h"

namespace engine {
void engine::Surface::accept(engine::IRenderVisitor& visitor) const
{
    visitor.visit(*this);
}

common::Vector2D<int> Surface::position() const
{
    return m_position;
}

common::Vector2D<int> Surface::size() const
{
    return m_size;
}

int Surface::alpha() const
{
    return m_alpha;
}

void Surface::draw(const IGraphicsElement* shape)
{
    m_shapes.push_back(shape);
}

std::vector<const IGraphicsElement*> Surface::shapes() const
{
    return m_shapes;
}

bool Surface::operator==(const Surface& rhs) const
{
    return m_position == rhs.m_position && m_size == rhs.m_size && m_alpha == rhs.m_alpha && m_shapes == rhs.m_shapes;
}

bool Surface::operator!=(const Surface& rhs) const
{
    return !(rhs == *this);
}

void Surface::alpha(int alpha)
{
    m_alpha = alpha;
}
}
