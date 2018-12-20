

#include "MenuSlider.h"

namespace game::ui {
MenuSlider::MenuSlider(engine::ui::ComponentSize size, double minimum, double maximum, double value)
    : NumericSlider(size, minimum, maximum, value)
    , m_slider("assets/sprites/ui/menu_slider.png", { 0, 0 }, { 0, 0 })
    , m_selectedSliderKnob("assets/sprites/ui/menu_slider_knob_selected.png", { 0, 0 }, { 0, 0 })
    , m_unselectedSliderKnob("assets/sprites/ui/menu_slider_knob_unselected.png", { 0, 0 }, { 0, 0 })
    , m_arrowLeft("assets/sprites/ui/arrow.png", { 0, 0 }, { 0, 0 })
    , m_arrowRight("assets/sprites/ui/arrow.png", { 0, 0 }, { 0, 0 })
    , m_valueBox("assets/sprites/ui/menu_box.png", { 0, 0 }, { 0, 0 })
{
    m_arrowRight.setFlippedHorizontal(true);
    m_valueFont.setColor(engine::Color{ 255, 255, 255, 255 });
}

engine::ui::DrawContext MenuSlider::draw(engine::ui::DrawContext context)
{
    return NumericSlider::draw(context);
}

void MenuSlider::drawLine(engine::ui::DrawContext context, const common::Vector2D<int>& calculatedSize)
{
    const auto lineStart = context.pos + common::Vector2D<int>(0, calculatedSize.y - 30);
    const auto lineEnd = lineStart + common::Vector2D<int>(calculatedSize.x, 0);
    const auto size = common::Vector2D<int>(lineEnd.x - lineStart.x, 30);

    m_slider.setPosition({ lineStart.x, lineStart.y });
    m_slider.setSize(size);
    context.renderer.draw(m_slider);
}

void MenuSlider::drawValueBox(engine::ui::DrawContext context, const common::Vector2D<int>& calculatedSize)
{
    auto valueBoxSize = m_minBoxSize;
    if (m_printValue) {
        valueBoxSize = getBoxSize(m_valueFont, context.renderer);
    }
    double progress = (m_value - m_minimum) / (m_maximum - m_minimum);
    const common::Vector2D<int> valueBoxPos{ context.pos.x + static_cast<int>(progress * (calculatedSize.x - valueBoxSize.x)),
        context.pos.y };
    //RectangleShape valueBox{ valueBoxPos, valueBoxSize, isSelected ? m_selectedColor : m_valueBackgroundColor };
    auto& knobToDraw = context.focusedComponent == this ? m_selectedSliderKnob : m_unselectedSliderKnob;
    knobToDraw.setPosition(valueBoxPos + common::Vector2D<int>{ 0, 5 });
    knobToDraw.setSize({ 30, 30 });

    if (context.focusedComponent == this) {
        m_valueBox.setPosition(knobToDraw.position() + common::Vector2D<int>(knobToDraw.size().x - 5, 0));
        m_valueBox.setSize({ 50, 30 });
        context.renderer.draw(m_valueBox);
        m_valueFont.setPosition(m_valueBox.position() + common::Vector2D<int>(15, 0));
        context.renderer.draw(m_valueFont);
    }

    context.renderer.draw(knobToDraw);
}

void MenuSlider::drawMinimumBox(engine::ui::DrawContext context)
{
    m_arrowLeft.setPosition(m_slider.position() + common::Vector2D<int>(-30, 0));
    m_arrowLeft.setSize({ 30, 30 });
    context.renderer.draw(m_arrowLeft);
}

void MenuSlider::drawMaximumBox(engine::ui::DrawContext context, const common::Vector2D<int>& /*calculatedSize*/)
{

    m_arrowRight.setPosition(m_slider.position() + common::Vector2D<int>(m_slider.size().x, 0));
    m_arrowRight.setSize({ 30, 30 });
    context.renderer.draw(m_arrowRight);
}
}
