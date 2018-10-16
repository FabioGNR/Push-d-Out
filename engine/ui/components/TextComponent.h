#pragma once

#include "Component.h"
#include <graphics/drawable/Font.h>

namespace engine {
namespace ui {
    class TextComponent {
    public:
        explicit TextComponent(const std::string& text, int textSize = 14)
            : m_font{
                "assets/fonts/Pixeled.ttf", text, textSize, Color(), common::Vector2D<int>(0,0)
            }
        {
        }
        void setTextSize(int size);
        void setFont(const std::string& fontPath);
        void setTextColor(const Color& color);

    protected:
        Font m_font;
        common::Vector2D<int> calculateTextSize(const IRenderer& renderer) const;
    };
}
}