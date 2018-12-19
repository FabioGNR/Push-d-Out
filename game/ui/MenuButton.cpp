#include "MenuButton.h"

namespace game::ui {
MenuButton::MenuButton(const engine::ui::ComponentSize& size, const std::string& text, std::function<void()> onHover, int textSize)
    : Button(size, text, textSize)
    , m_button("assets/sprites/ui/menu_button.png", { 0, 0 }, { 0, 0 })
    , m_buttonActiveLeft("assets/sprites/ui/menu_button_side.png", { 0, 0 }, { 0, 0 })
    , m_buttonActiveRight("assets/sprites/ui/menu_button_side.png", { 0, 0 }, { 0, 0 })
    , m_onHover(std::move(onHover))
{
    m_buttonActiveLeft.setFlippedHorizontal(true);
}

engine::ui::DrawContext MenuButton::draw(engine::ui::DrawContext context)
{
    /*
     * Entirely butchering the UI system, but thats what you get when u need to get shit done and have no time
     * /shrug
     *
     * Sorry.
     */

    common::Vector2D<int> calculatedSize = calculateSize(context.renderer, context.availableSize);
    // Scale size up so the buttons are bigger
    calculatedSize.x *= 3;
    calculatedSize.y *= 2;

    auto drawPosition = context.pos;
    drawPosition.x -= calculatedSize.x / 3;

    m_button.setPosition(drawPosition);
    m_button.setSize(calculatedSize);

    context.renderer.draw(m_button);

    if (context.focusedComponent == this) {
        // Add "side sprites" and make sure they align with the button
        auto size = calculatedSize;
        size.y /= 1.5f;
        size.x = 30;

        m_buttonActiveRight.setSize(size);
        m_buttonActiveLeft.setSize(size);

        auto leftPos = drawPosition;
        leftPos.y += 15;
        leftPos.x -= size.x;

        auto rightPos = drawPosition;
        rightPos.y += 15;
        rightPos.x += calculatedSize.x;

        m_buttonActiveLeft.setPosition(leftPos);
        m_buttonActiveRight.setPosition(rightPos);

        context.renderer.draw(m_buttonActiveLeft);
        context.renderer.draw(m_buttonActiveRight);

        m_onHover();
    }

    common::Vector2D<int> requiredTextSize = calculateTextSize(context.renderer);

    m_font.setPosition(drawPosition + (calculatedSize - requiredTextSize) / 2);
    context.renderer.draw(m_font);
    context.pos += calculatedSize;
    return context;
}

void MenuButton::onHover(std::function<void()> onHover)
{
    m_onHover = std::move(onHover);
}
}
