#include "TextComponent.h"
namespace engine {
namespace ui {

    void TextComponent::setTextSize(int size)
    {
        m_font.setFontSize(size);
    }

    common::Vector2D TextComponent::calculateTextSize() const
    {
        //TODO: implement calculation
        return common::Vector2D(100, 30);
    }
}
}