#pragma once
#include "Component.h"
#include "TextComponent.h"
#include <string>

namespace engine {
namespace ui {
    class Label : public Component, public TextComponent {
    public:
        Label(ComponentSize size, const std::string& text, int textSize = 12)
            : Component(size)
            , TextComponent(text, textSize)
        {
        }

        common::Vector2D<int> calculateSize(const IRenderer &renderer, common::Vector2D<int> availableSize) const override;

        DrawContext draw(DrawContext context) override;
    };
}
}