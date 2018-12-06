#pragma once

#include <engine/graphics/IGraphicsElement.h>
#include <engine/graphics/IRenderer.h>
#include <engine/graphics/drawable/Font.h>

#include <chrono>

namespace game::hud {
class FpsCounter : public engine::IGraphicsElement {
    mutable int m_count = 0;
    mutable int m_displayCount = 0;
    mutable std::chrono::time_point<std::chrono::high_resolution_clock> m_last;

    mutable engine::Font m_font;

    common::Vector2D<int> m_position;

public:
    explicit FpsCounter(const common::Vector2D<int>& position);
    ~FpsCounter() override = default;

    const common::Vector2D<int>& position() const override;
    void setPosition(const common::Vector2D<int>& position) override;

    void draw(const engine::IRenderer& renderer) const override;
};
}
