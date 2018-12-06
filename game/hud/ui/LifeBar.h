#pragma once

#include <engine/graphics/IGraphicsElement.h>
#include <engine/graphics/drawable/Sprite.h>

#include <memory>
#include <vector>

namespace game::hud::ui {
class LifeBar : public engine::IGraphicsElement {
    common::Vector2D<int> m_beginPosition;
    int m_totalLifes;

    std::vector<std::unique_ptr<engine::Sprite>> m_hearts;

public:
    LifeBar(const common::Vector2D<int>& beginPosition, int totalLifes);
    ~LifeBar() override = default;

    const common::Vector2D<int>& position() const override;
    void setPosition(const common::Vector2D<int>& position) override;

    void draw(const engine::IRenderer& renderer) const override;

    void setRemainingHearts(int lifes);
};
}
