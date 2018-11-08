#include <utility>

#include <utility>

#include "Font.h"

#include <graphics/IRenderVisitor.h>

namespace engine {

Font::Font(std::string fontPath, std::string text, int fontSize, Color color, common::Vector2D<int> position)
    : m_fontPath(std::move(fontPath))
    , m_text(std::move(text))
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

common::Vector2D<int> Font::position() const
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

void Font::setPosition(common::Vector2D<int> position)
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

bool Font::operator==(const Font& rhs) const
{
    return m_fontPath == rhs.m_fontPath
        && m_text == rhs.m_text
        && m_fontSize == rhs.m_fontSize
        && m_color == rhs.m_color;
}

bool Font::operator!=(const Font& rhs) const
{
    return !(rhs == *this);
}

} // end namespace engine
