#include "Sprite.h"

#include <graphics/IRenderVisitor.h>

namespace engine {
Sprite::Sprite(const std::string& spritePath, int x, int y, int width, int height, double scale)
    : m_spritePath(spritePath)
    , m_x(x)
    , m_y(y)
    , m_width(width)
    , m_height(height)
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

int Sprite::x() const
{
    return m_x;
}

int Sprite::y() const
{
    return m_y;
}

int Sprite::width() const
{
    return m_width;
}

int Sprite::height() const
{
    return m_height;
}

double Sprite::scale() const
{
    return m_scale;
}

} // end namespace engine
