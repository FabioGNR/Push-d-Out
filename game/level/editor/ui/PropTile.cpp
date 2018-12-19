#include "PropTile.h"

#include <engine/common/RNG.h>
#include <engine/graphics/IRenderer.h>

namespace game::level::editor::ui {
PropTile::PropTile(const common::Vector2D<int>& position, const common::Vector2D<int>& size)
    : ITile(TileType::PROP, position, size)
{
}

void PropTile::draw(const engine::IRenderer& renderer) const
{
    ITile::draw(renderer);
}

void PropTile::setPosition(const common::Vector2D<int>& position)
{
    ITile::setPosition(position);
}
} // end namespace game::level
