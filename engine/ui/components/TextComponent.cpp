#include "TextComponent.h"
namespace engine {
namespace ui {

    void TextComponent::setTextSize(int size)
    {
        m_font.setFontSize(size);
    }

    common::Vector2D<int> TextComponent::calculateTextSize() const
    {
        //TODO: implement calculation
        return {100, 30};
    }
}
}