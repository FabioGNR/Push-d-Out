#include "TileSpriteSelectionScrollbar.h"

#include <engine/graphics/IRenderer.h>
#include <engine/graphics/drawable/Sprite.h>

namespace game::level::editor::ui {
TileSpriteSelectionScrollbar::TileSpriteSelectionScrollbar(
    TileSet& tileSet,
    const common::Vector2D<int>& position,
    const common::Vector2D<int>& size)
    : m_tileSet(tileSet)
    , m_backgroundShape("assets/sprites/button.png", position, size)
{
}

void TileSpriteSelectionScrollbar::draw(const engine::IRenderer& renderer) const
{
    renderer.draw(m_backgroundShape);

    const int fittedSquareSize = static_cast<int>(
        std::min(m_backgroundShape.size().x * 0.75, m_backgroundShape.size().y * 0.75));

    const auto chosenBlockSize = common::Vector2D<int>(fittedSquareSize, fittedSquareSize);
    const auto otherBlockSizes = common::Vector2D<int>(
        fittedSquareSize / 2,
        fittedSquareSize / 2);

    const auto& tiles = m_tileSet.getRangeFromCurrent(3);
    for (size_t i = 0; i < tiles.size(); ++i) {
        const auto& bestSize = i == 1 ? chosenBlockSize : otherBlockSizes;

        auto position = m_backgroundShape.position();
        position.y += m_backgroundShape.size().y / 4;

        if (i == 1) {
            position.x += (m_backgroundShape.size().x / 3) * i - 5;
            position.y -= 5;
        } else {
            position.x += (m_backgroundShape.size().x / 3) * i + 15;
        }

        const auto sprite = [&]() {
            if (tiles[i].empty()) {
                return engine::Sprite("assets/sprites/eraser.png", position, bestSize);
            }
            return engine::Sprite(tiles[i], position, bestSize);
        }();

        renderer.draw(sprite);
    }
}

void TileSpriteSelectionScrollbar::setPosition(const common::Vector2D<int>& position)
{
    m_backgroundShape.setPosition(position);
}

const common::Vector2D<int>& TileSpriteSelectionScrollbar::getSize()
{
    return m_backgroundShape.size();
}

void TileSpriteSelectionScrollbar::setSize(const common::Vector2D<int>& size)
{
    m_backgroundShape.setSize(size);
}

const common::Vector2D<int>& TileSpriteSelectionScrollbar::position() const
{
    return m_backgroundShape.position();
}
} // end namespace
