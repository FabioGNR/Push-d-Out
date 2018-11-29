#include <utility>

#include "Sprite.h"

#include <graphics/IRenderVisitor.h>

namespace engine {
Sprite::Sprite(std::string spritePath, common::Vector2D<int> position, common::Vector2D<int> sourceSize, common::Vector2D<int> sourcePosition)
    : m_spritePath(std::move(spritePath))
    , m_position(position)
    , m_size(sourceSize)
    , m_sourcePosition{ sourcePosition }
    , m_sourceSize(sourceSize)
{
}

Sprite::Sprite(std::string spritePath, common::Vector2D<int> position, common::Vector2D<int> size)
    : m_spritePath(std::move(spritePath))
    , m_position(position)
    , m_size(size)
    , m_sourcePosition{ common::Vector2D<int>(0, 0) }
    , m_sourceSize{ size }
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

void Sprite::spritePath(std::string path)
{
    m_spritePath = std::move(path);
}

const common::Vector2D<int>& Sprite::position() const
{
    return m_position;
}

const common::Vector2D<int>& Sprite::sourcePosition() const
{
    return m_sourcePosition;
}

const common::Vector2D<int>& Sprite::sourceSize() const
{
    return m_sourceSize;
}

const common::Vector2D<int>& Sprite::size() const
{
    return m_size;
}

void Sprite::setPosition(const common::Vector2D<int>& position)
{
    m_position = position;
}

void Sprite::setSize(const common::Vector2D<int>& size)
{
    m_size = size;
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
