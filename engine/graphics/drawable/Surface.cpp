#include "Surface.h"

#include "graphics/IRenderVisitor.h"
#include "graphics/IRenderer.h"

namespace engine {

void engine::Surface::accept(const IRenderVisitor& visitor) const
{
    visitor.visit(*this);
}

const common::Vector2D<int>& Surface::position() const
{
    return m_position;
}

const common::Vector2D<int>& Surface::size() const
{
    return m_size;
}

int Surface::alpha() const
{
    return m_alpha;
}

bool Surface::operator==(const Surface& rhs) const
{
    return m_position == rhs.m_position
        && m_size == rhs.m_size
        && m_alpha == rhs.m_alpha
        && m_shapes == rhs.m_shapes;
}

bool Surface::operator!=(const Surface& rhs) const
{
    return !(rhs == *this);
}

void Surface::setAlpha(int alpha)
{
    m_alpha = std::clamp(alpha, 0, 255);
}

void Surface::draw(const IRenderer& renderer) const
{
    for (const auto& shape : m_shapes) {
        shape->draw(renderer);
    }
}

void Surface::addShape(std::unique_ptr<IGraphicsElement> shape)
{
    m_shapes.push_back(std::move(shape));
}
void Surface::setPosition(const common::Vector2D<int>& position)
{
    m_position = position;
}

void Surface::setSize(const common::Vector2D<int>& size)
{
    m_size = size;
}
}
