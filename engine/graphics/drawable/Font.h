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

    common::Vector2D<int> m_position;

public:
    Font(const std::string& fontPath, const std::string& text, int fontSize, const Color& color, common::Vector2D<int> position);

    void accept(IRenderVisitor& visitor) const override;

    const std::string& text() const;

    const std::string& fontPath() const;

    common::Vector2D<int> position() const;
    int fontSize() const;
    const Color& color() const;

    void setText(const std::string& text);
    void setFontSize(int fontSize);
    void setPosition(common::Vector2D<int> position);
    void setColor(const Color& color);

    bool operator==(const Font &rhs) const;
    bool operator!=(const Font &rhs) const;
};
} // end namespace engine
