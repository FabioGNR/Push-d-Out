#include "Font.h"

#include <graphics/IRenderVisitor.h>

namespace engine {

Font::Font(const std::string& fontPath, const std::string& text, int fontSize, const Color& color, common::Vector2D position)
    : m_fontPath(fontPath)
    , m_text(text)
    , m_fontSize(fontSize)
    , m_color(color)
    , m_position(position)
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

common::Vector2D Font::position() const
{
    return m_position;
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

void Font::setPosition(common::Vector2D position)
{
    m_position = position;
}

const Color& Font::color() const
{
    return m_color;
}

void Font::setColor(const Color& color)
{
    m_color = color;
}

} // end namespace engine
