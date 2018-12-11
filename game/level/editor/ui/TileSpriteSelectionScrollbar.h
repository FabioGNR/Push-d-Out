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
class TileSpriteSelectionScrollbar : public engine::IGraphicsElement {
    TileSet* m_tileSet;
    engine::Sprite m_backgroundShape;

public:
    TileSpriteSelectionScrollbar(TileSet* tileSet, const common::Vector2D<int>& position, const common::Vector2D<int>& size);

    ~TileSpriteSelectionScrollbar() override = default;
    void draw(const engine::IRenderer& renderer) const override;
    const common::Vector2D<int>& position() const override;
    void setPosition(const common::Vector2D<int>& position) override;

    const common::Vector2D<int>& getSize();
    void setSize(const common::Vector2D<int>& size);
};
} // end namespace
