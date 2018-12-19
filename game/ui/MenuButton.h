#pragma once

#include <engine/ui/components/Button.h>
#include <functional>

namespace game::ui {
class MenuButton : public engine::ui::Button {
    engine::Sprite m_button;
    engine::Sprite m_buttonActiveLeft;
    engine::Sprite m_buttonActiveRight;

    std::function<void()> m_onHover;

public:
    MenuButton(const engine::ui::ComponentSize& size, const std::string& text, std::function<void()> onHover = [] {}, int textSize = 12);
    ~MenuButton() override = default;

    engine::ui::DrawContext draw(engine::ui::DrawContext context) override;
    void onHover(std::function<void()> onHover);
};
}
