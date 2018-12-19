#pragma once
#include "Component.h"
#include "TextComponent.h"
#include <string>

namespace engine {
namespace ui {
    class Label : public Component, public TextComponent {
    private:
        Color m_color;
    public:
        Label(ComponentSize size, const std::string& text, int textSize = 12, Color color = Color{0, 0, 0})
            : Component(size)
            , TextComponent(text, textSize)
            , m_color{color}
        {
        }

        ~Label() override = default;

        common::Vector2D<int> calculateSize(const IRenderer& renderer, common::Vector2D<int> availableSize) const override;

        DrawContext draw(DrawContext context) override;
    };
}
}