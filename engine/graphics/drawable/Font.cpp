#include "Font.h"

#include <graphics/IRenderVisitor.h>

namespace engine {

Font::Font(const std::string& fontPath, const std::string& text, int fontSize, const Color& color, int x, int y)
    : m_fontPath(fontPath)
    , m_text(text)
    , m_fontSize(fontSize)
    , m_color(color)
    , m_x(x)
    , m_y(y)
{
}

void Font::accept(engine::IRenderVisitor& visitor) const
{
    visitor.visit(*this);
}

const std::string& Font::text() const
{
    return m_text;
}

const std::string& Font::fontPath() const
{
    return m_fontPath;
}

int Font::x() const
{
    return m_x;
}

int Font::y() const
{
    return m_y;
}

int Font::fontSize() const
{
    return m_fontSize;
}

void Font::setText(const std::string& text)
{
    m_text = text;
}

void Font::setFontSize(int fontSize)
{
    m_fontSize = fontSize;
}

void Font::setX(int x)
{
    m_x = x;
}

void Font::setY(int y)
{
    m_y = y;
}

const Color& Font::color() const
{
    return m_color;
}

} // end namespace engine
