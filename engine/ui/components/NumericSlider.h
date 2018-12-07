#pragma once
#include "Component.h"
#include <engine/graphics/drawable/Font.h>

namespace engine::ui {
class NumericSlider : public Component {
private:
    double m_minimum;
    double m_maximum;
    double m_value;
    bool m_printValue{ true };
    Font m_minimumFont;
    Font m_maximumFont;
    Font m_valueFont;
    const common::Vector2D<int> m_minBoxSize{ 20, 20 };
    const common::Vector2D<int> m_boxFontPadding{ 5, 5 };
    const Color m_selectedColor{ 0, 255, 255 };
    const Color m_valueBackgroundColor{ 255, 255, 255 };
    const Color m_boundBackgroundColor{ 155, 155, 155 };
    common::Vector2D<int> getBoxSize(const Font& font, const IRenderer& renderer) const;

    std::string formatNumber(double number);

    void drawLine(DrawContext context, const common::Vector2D<int>& calculatedSize);
    void drawValueBox(DrawContext context, const common::Vector2D<int>& calculatedSize);
    void drawMinimumBox(DrawContext context);
    void drawMaximumBox(DrawContext context, const common::Vector2D<int>& calculatedSize);

public:
    NumericSlider(ComponentSize size, double minimum, double maximum, double value)
        : Component(size)
        , m_minimum{ minimum }
        , m_maximum{ maximum }
        , m_value{ value }
        , m_minimumFont{ "assets/fonts/Pixeled.ttf", formatNumber(m_minimum), 10, Color(0, 0, 0), { 0, 0 } }
        , m_maximumFont{ "assets/fonts/Pixeled.ttf", formatNumber(m_maximum), 10, Color(0, 0, 0), { 0, 0 } }
        , m_valueFont{ "assets/fonts/Pixeled.ttf", formatNumber(m_value), 10, Color(0, 0, 0), { 0, 0 } }
    {
    }

    DrawContext draw(DrawContext context) override;

    common::Vector2D<int> calculateSize(const IRenderer& renderer, common::Vector2D<int> availableSize) const override;

    void processInputEvent(engine::input::maps::InputMap& map) override;

    bool isNavigatable() override;

    void setValue(double value);

    double getValue() const;
};
}