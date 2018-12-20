#include <utility>

#include "Sprite.h"

#include "graphics/IRenderer.h"
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

void Sprite::accept(const IRenderVisitor& visitor) const
{
    visitor.visit(*this);
}

const std::string& Sprite::spritePath() const
{
    return m_spritePath;
}

void Sprite::setSpritePath(std::string spritePath)
{
    m_spritePath = std::move(spritePath);
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

void Sprite::setFlippedVertical(bool isFlipped)
{
    m_flippedVertical = isFlipped;
}

void Sprite::setFlippedHorizontal(bool isFlipped)
{
    m_flippedHorizontal = isFlipped;
}

void Sprite::setRotation(double rotation)
{
    m_rotation = rotation;
}

bool Sprite::operator==(const Sprite& rhs) const
{
    return m_spritePath == rhs.m_spritePath && m_flippedHorizontal == rhs.m_flippedHorizontal && m_flippedVertical == rhs.m_flippedVertical;
}

bool Sprite::operator!=(const Sprite& rhs) const
{
    return !(rhs == *this);
}

void Sprite::draw(const IRenderer& renderer) const
{
    renderer.draw(*this);
}

bool Sprite::isFlippedVertical() const
{
    return m_flippedVertical;
}

bool Sprite::isFlippedHorizontal() const
{
    return m_flippedHorizontal;
}

double Sprite::getRotation() const
{
    return m_rotation;
}

void Sprite::setRotationCenter(const common::Vector2D<double>& center)
{
    m_rotationCenter = common::Vector2D<double>(center.x, center.y);
}

const common::Vector2D<double>& Sprite::getRotationCenter() const
{
    return m_rotationCenter;
}
} // end namespace engine
