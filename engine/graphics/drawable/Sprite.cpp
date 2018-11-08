#include <utility>

#include "Sprite.h"

#include <graphics/IRenderVisitor.h>

namespace engine {
Sprite::Sprite(std::string spritePath, common::Vector2D<int> position, common::Vector2D<int> size, double scale)
    : m_spritePath(std::move(spritePath))
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

common::Vector2D<int> Sprite::position() const
{
    return m_position;
}

common::Vector2D<int> Sprite::size() const
{
    return m_size;
}

double Sprite::scale() const
{
    return m_scale;
}

bool Sprite::operator==(const Sprite& rhs) const
{
    return m_spritePath == rhs.m_spritePath;
}

bool Sprite::operator!=(const Sprite& rhs) const
{
    return !(rhs == *this);
}

} // end namespace engine
