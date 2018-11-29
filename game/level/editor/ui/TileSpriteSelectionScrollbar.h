#pragma once

#include "TileSet.h"

#include <engine/common/Vector2D.h>
#include <engine/graphics/drawable/Sprite.h>

#include <array>
#include <memory>

namespace engine {
class IRenderer;
}

namespace game::level::editor::ui {
class TileSpriteSelectionScrollbar {
    TileSet& m_tileSet;
    engine::Sprite m_backgroundShape;

public:
    TileSpriteSelectionScrollbar(TileSet& tileSet, const common::Vector2D<int>& position, const common::Vector2D<int>& size);
    void draw(engine::IRenderer& renderer);
    const common::Vector2D<int>& getPosition() const;
    void setPosition(const common::Vector2D<int>& position);

    const common::Vector2D<int>& getSize();
    void setSize(const common::Vector2D<int>& size);
};
} // end namespace
