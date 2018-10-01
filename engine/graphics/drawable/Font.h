#pragma once

#include <string>

#include <graphics/Color.h>
#include <graphics/IGraphicsElement.h>

namespace engine {
class Font : public IGraphicsElement {
    std::string m_fontPath;
    std::string m_text;
    int m_fontSize;
    Color m_color;

    // TODO: Use Vector2d's for coordinates.
    int m_x, m_y;

public:
    Font(const std::string& fontPath, const std::string& text, int fontSize, const Color& color, int x, int y);

    void accept(IRenderVisitor& visitor) const override;

    const std::string& text() const;

    const std::string& fontPath() const;

    int x() const;
    int y() const;
    int fontSize() const;
    const Color& color() const;

    void setText(const std::string& text);
    void setFontSize(int fontSize);
    void setX(int x);
    void setY(int y);
};
} // end namespace engine
