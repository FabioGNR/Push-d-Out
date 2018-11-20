#include <utility>

#include "Sprite.h"

#include <graphics/IRenderVisitor.h>

namespace engine {
Sprite::Sprite(std::string spritePath, common::Vector2D<int> position, common::Vector2D<int> sourceSize, common::Vector2D<int> sourcePosition, common::Vector2D<double> scale)
    : m_spritePath(std::move(spritePath))
    , m_sourcePosition{sourcePosition}
    , m_position(position)
    , m_sourceSize(sourceSize)
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

common::Vector2D<int> Sprite::sourcePosition() const
{
    return m_sourcePosition;
}

common::Vector2D<int> Sprite::sourceSize() const
{
    return m_sourceSize;
}

common::Vector2D<double> Sprite::scale() const
{
    return m_scale;
}

bool Sprite::operator==(const Sprite& rhs) const
{
    return (m_spritePath == rhs.m_spritePath && m_position == rhs.position() && m_sourceSize == rhs.sourceSize());
}

bool Sprite::operator!=(const Sprite& rhs) const
{
    return !(rhs == *this);
}

void Sprite::setPosition(common::Vector2D<int> position)
{
    m_position = position;
}

void Sprite::setSize(common::Vector2D<int> size)
{
    m_size = size;
}

common::Vector2D<int> Sprite::size() const {
    return m_size;
}

} // end namespace engine
