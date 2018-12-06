#pragma once

#include <engine/graphics/drawable/Sprite.h>

namespace engine {
class IRenderer;
}

namespace game::level::editor::ui {
class Cursor : public engine::IGraphicsElement {
    engine::Sprite m_cursorSprite;

public:
    explicit Cursor(const std::string& cursorSprite);
    ~Cursor() override = default;

    void draw(const engine::IRenderer& renderer) const override;
    const common::Vector2D<int>& position() const override;
    void setPosition(const common::Vector2D<int>& position) override;
};

} // end namespace