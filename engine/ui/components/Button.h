#pragma once
#include "Component.h"
#include "IAction.h"
#include "TextComponent.h"
#include <graphics/drawable/Font.h>
#include <memory>
#include <string>

namespace engine {
namespace ui {
    class Button : public Component, public TextComponent {
    public:
        Button(ComponentSize size, const std::string& text, int textSize = 12)
            : Component(size)
            , TextComponent(text, textSize)
        {
        }

        DrawContext draw(DrawContext context) override;

        void setAction(std::unique_ptr<IAction> action)
        {
            m_action = std::move(action);
        }

        void processInputEvent() override;

        common::Vector2D<int> calculateSize(common::Vector2D<int> availableSize) const override;

        bool isNavigatable() override;

    private:
        std::unique_ptr<IAction> m_action;
    };
}
}