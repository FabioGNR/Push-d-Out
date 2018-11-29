#include "PlatformTile.h"

#include <engine/common/RNG.h>
#include <engine/graphics/IRenderer.h>

namespace game::level::editor::ui {
PlatformTile::PlatformTile(const common::Vector2D<int>& position, const common::Vector2D<int>& size)
    : ITile(TileType::PLATFORM)
    , m_boundingBoxShape(position, size, engine::Color(255, 0, 0, 255), false)
    , m_tileSprite(nullptr)
{
}

void PlatformTile::draw(engine::IRenderer& renderer)
{
    // always draw bounding box
    renderer.draw(m_boundingBoxShape);

    // if user has picked a sprite for this tile, draw the sprite as well
    if (m_tileSprite != nullptr) {
        renderer.draw(*m_tileSprite);
    }
}
void PlatformTile::select(bool value)
{
    ITile::select(value);
}
const common::Vector2D<int>& PlatformTile::getPosition() const
{
    return m_boundingBoxShape.position();
}
void PlatformTile::setTileSprite(const std::string& spriteName)
{
    if (spriteName.empty()) {
        m_tileSprite = nullptr;
    } else {
        m_tileSprite = std::make_unique<engine::Sprite>(
            spriteName, m_boundingBoxShape.position(), m_boundingBoxShape.size());
    }
}

const engine::Sprite* PlatformTile::getTileSprite() const
{
    return m_tileSprite.get();
}
} // end namespace game::level
