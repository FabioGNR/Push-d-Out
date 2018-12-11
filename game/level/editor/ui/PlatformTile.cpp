#include "PlatformTile.h"

#include <engine/common/RNG.h>
#include <engine/graphics/IRenderer.h>

namespace game::level::editor::ui {
PlatformTile::PlatformTile(const common::Vector2D<int>& position, const common::Vector2D<int>& size)
    : ITile(TileType::PLATFORM, position, size)
    , m_boundingBoxShape(position, size, engine::Color(255, 0, 0, 25), false)
{
}

void PlatformTile::draw(const engine::IRenderer& renderer) const
{
    // always draw bounding box
    renderer.draw(m_boundingBoxShape);
    ITile::draw(renderer);
}

void PlatformTile::setPosition(const common::Vector2D<int>& position)
{
    ITile::setPosition(position);
    m_boundingBoxShape.setPosition(position);
}
} // end namespace game::level
