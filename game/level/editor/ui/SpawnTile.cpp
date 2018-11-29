#include "SpawnTile.h"

#include <engine/graphics/IRenderer.h>

namespace game::level::editor::ui {
SpawnTile::SpawnTile(const common::Vector2D<int>& position, const common::Vector2D<int>& size)
    : ITile(TileType::SPAWN)
    , m_boundingBoxShape(position, size, engine::Color(0, 0, 255, 255), false)
    , m_tileSprite(nullptr)
{
}

void SpawnTile::draw(engine::IRenderer& renderer)
{
    // always draw bounding box
    renderer.draw(m_boundingBoxShape);

    // if user has picked a sprite for this tile, draw the sprite as well
    if (m_tileSprite != nullptr) {
        renderer.draw(*m_tileSprite);
    }
}

void SpawnTile::select(bool value)
{
    ITile::select(value);

    if (isSelected()) {
        m_tileSprite = std::make_unique<engine::Sprite>(
            "assets/sprites/spawn_dummy.png",
            common::Vector2D<int>{ m_boundingBoxShape.position().x, m_boundingBoxShape.position().y - m_boundingBoxShape.size().y },
            common::Vector2D<int>{ 122, 146 });
        m_tileSprite->setSize({ 30, 60 });
    } else {
        m_tileSprite = nullptr;
    }
}

const common::Vector2D<int>& SpawnTile::getPosition() const
{
    return m_boundingBoxShape.position();
}
}
