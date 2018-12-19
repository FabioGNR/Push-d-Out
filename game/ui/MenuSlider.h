#pragma once

#include <engine/ui/components/NumericSlider.h>

namespace game::ui {
class MenuSlider : public engine::ui::NumericSlider {
    engine::Sprite m_slider;
    engine::Sprite m_selectedSliderKnob;
    engine::Sprite m_unselectedSliderKnob;
    engine::Sprite m_arrowLeft;
    engine::Sprite m_arrowRight;
    engine::Sprite m_valueBox;

public:
    MenuSlider(engine::ui::ComponentSize size, double minimum, double maximum, double value);
    engine::ui::DrawContext draw(engine::ui::DrawContext context) override;

protected:
    void drawLine(engine::ui::DrawContext context, const common::Vector2D<int>& calculatedSize) override;

    void drawValueBox(engine::ui::DrawContext context, const common::Vector2D<int>& calculatedSize) override;

    void drawMinimumBox(engine::ui::DrawContext context) override;

    void drawMaximumBox(engine::ui::DrawContext context, const common::Vector2D<int>& calculatedSize) override;
};
}
