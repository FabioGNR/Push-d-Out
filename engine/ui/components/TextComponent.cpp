#include "TextComponent.h"
namespace engine {
namespace ui {

    void TextComponent::setTextSize(int size)
    {
        m_font.setFontSize(size);
    }

    common::Vector2D<int> TextComponent::calculateTextSize(const IRenderer& renderer) const
    {
        return renderer.getFontSize(m_font);
    }

    void TextComponent::setFont(const std::string& fontPath)
    {
        (void)fontPath;
        //TODO: Engine::Font has no setFont
    }

    void TextComponent::setTextColor(const Color& color)
    {
        m_font.setColor(color);
    }
}
}