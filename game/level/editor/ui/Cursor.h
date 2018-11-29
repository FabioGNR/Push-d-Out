#pragma once

#include <engine/graphics/drawable/Sprite.h>

namespace engine {
class IRenderer;
}

namespace game::level::editor::ui {
class Cursor {
    engine::Sprite m_cursorSprite;

public:
    explicit Cursor(const std::string& cursorSprite);
    void draw(engine::IRenderer& renderer) const;
    void setPosition(common::Vector2D<int> position);
};

} // end namespace