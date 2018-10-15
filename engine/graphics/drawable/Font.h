#pragma once

#include <string>

#include <common/Vector2D.h>
#include <graphics/Color.h>
#include <graphics/IGraphicsElement.h>

namespace engine {
class Font : public IGraphicsElement {
    std::string m_fontPath;
    std::string m_text;
    int m_fontSize;
    Color m_color;

    common::Vector2D m_position;

public:
    Font(const std::string& fontPath, const std::string& text, int fontSize, const Color& color, common::Vector2D position);

    void accept(IRenderVisitor& visitor) const override;

    const std::string& text() const;

    const std::string& fontPath() const;

    common::Vector2D position() const;
    int fontSize() const;
    const Color& color() const;

    void setText(const std::string& text);
    void setFontSize(int fontSize);
    void setPosition(common::Vector2D position);
    void setColor(const Color& color);
};
} // end namespace engine
