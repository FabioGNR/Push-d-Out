#include "NumericSlider.h"
#include <engine/graphics/drawable/Font.h>
#include <engine/graphics/drawable/RectangleShape.h>
#include <graphics/drawable/LineShape.h>
#include <input/Keys.h>
#include <sstream>

namespace engine::ui {
DrawContext NumericSlider::draw(DrawContext context)
{
    const auto& calculatedSize = calculateSize(context.renderer, context.availableSize);
    drawLine(context, calculatedSize);
    drawMinimumBox(context);
    drawMaximumBox(context, calculatedSize);
    drawValueBox(context, calculatedSize);
    context.pos += calculatedSize;
    return context;
}

common::Vector2D<int> NumericSlider::calculateSize(const IRenderer& renderer, common::Vector2D<int> availableSize) const
{

    common::Vector2D<int> requiredSize{ 0, 0 };
    const auto& minimumBoxSize = getBoxSize(m_minimumFont, renderer);
    requiredSize.x += minimumBoxSize.x;
    const auto& maximumBoxSize = getBoxSize(m_minimumFont, renderer);
    requiredSize.x += maximumBoxSize.x;
    const auto& valueBoxSize = getBoxSize(m_minimumFont, renderer);
    requiredSize.x += valueBoxSize.x;
    requiredSize.y = std::max(valueBoxSize.y, std::max(minimumBoxSize.y, maximumBoxSize.y));
    return m_size.getSize(requiredSize, availableSize);
}

common::Vector2D<int> NumericSlider::getBoxSize(const Font& font, const IRenderer& renderer) const
{
    const auto fontSize = renderer.calculateFontSize(font);
    const auto requiredSize = fontSize + m_boxFontPadding; // bit of padding
    return common::Vector2D<int>::max(requiredSize, m_minBoxSize);
}

std::string NumericSlider::formatNumber(double number)
{
    std::ostringstream stream;
    stream << number;
    return stream.str();
}

void NumericSlider::processInputEvent(engine::input::maps::InputMap& map)
{
    using namespace input;
    bool decrease = map.hasState(Keys::A, States::DOWN) || map.getValue(AnalogKeys::CON_LEFTSTICK_X) < 0;
    if (decrease) {
        setValue(m_value - 1);
    }
    bool increase = map.hasState(Keys::D, States::DOWN) || map.getValue(AnalogKeys::CON_LEFTSTICK_X) > 0;
    if (increase) {
        setValue(m_value + 1);
    }
}

bool NumericSlider::isNavigatable()
{
    return true;
}

void NumericSlider::setValue(double value)
{
    m_value = std::max(m_minimum, std::min(m_maximum, value));
    m_valueFont.setText(formatNumber(m_value));
}

void NumericSlider::drawValueBox(DrawContext context, const common::Vector2D<int>& calculatedSize)
{
    auto valueBoxSize = m_minBoxSize;
    if (m_printValue) {
        valueBoxSize = getBoxSize(m_valueFont, context.renderer);
    }
    // calculate pos
    double progress = (m_value - m_minimum) / (m_maximum - m_minimum);
    const common::Vector2D<int> valueBoxPos{ context.pos.x + static_cast<int>(progress * (calculatedSize.x - valueBoxSize.x)),
        context.pos.y };
    // create background box
    bool isSelected = context.focusedComponent == this;
    RectangleShape valueBox{ valueBoxPos, valueBoxSize, isSelected ? m_selectedColor : m_valueBackgroundColor };
    // draw
    context.renderer.draw(valueBox);
    if (m_printValue) {
        m_valueFont.setPosition(valueBoxPos + (m_boxFontPadding / 2));
        context.renderer.draw(m_valueFont);
    }
}

void NumericSlider::drawMinimumBox(DrawContext context)
{
    const auto& minimumBoxSize = getBoxSize(m_minimumFont, context.renderer);
    RectangleShape minimumBox{ context.pos, minimumBoxSize, m_boundBackgroundColor };
    m_minimumFont.setPosition(context.pos + (m_boxFontPadding / 2));
    context.renderer.draw(minimumBox);
    context.renderer.draw(m_minimumFont);
}

void NumericSlider::drawMaximumBox(DrawContext context, const common::Vector2D<int>& calculatedSize)
{
    const auto& maximumBoxSize = getBoxSize(m_maximumFont, context.renderer);
    const common::Vector2D<int> maximumBoxPos{ (context.pos + calculatedSize).x - maximumBoxSize.x, context.pos.y };
    RectangleShape maximumBox{ maximumBoxPos, maximumBoxSize, m_boundBackgroundColor };
    m_maximumFont.setPosition(maximumBoxPos + (m_boxFontPadding / 2));
    context.renderer.draw(maximumBox);
    context.renderer.draw(m_maximumFont);
}

double NumericSlider::getValue() const
{
    return m_value;
}

void NumericSlider::drawLine(DrawContext context, const common::Vector2D<int>& calculatedSize)
{
    const auto lineStart = context.pos + common::Vector2D<int>(0, calculatedSize.y / 2);
    const auto lineEnd = lineStart + common::Vector2D<int>(calculatedSize.x, 0);
    // draw line between boxes
    LineShape lineShape{ lineStart, lineEnd, m_boundBackgroundColor };
    context.renderer.draw(lineShape);
}
}