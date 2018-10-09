#include "Sprite.h"

#include <graphics/IRenderVisitor.h>

namespace engine {
Sprite::Sprite(const std::string& spritePath, common::Vector2D position, common::Vector2D size, double scale)
    : m_spritePath(spritePath)
    , m_position(position)
    , m_size(size)
    , m_scale(scale)
{
}

void Sprite::accept(IRenderVisitor& visitor) const
{
    visitor.visit(*this);
}

const std::string& Sprite::spritePath() const
{
    return m_spritePath;
}

common::Vector2D Sprite::position() const
{
    return m_position;
}

common::Vector2D Sprite::size() const
{
    return m_size;
}

double Sprite::scale() const
{
    return m_scale;
}

} // end namespace engine
