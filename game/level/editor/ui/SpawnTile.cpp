#include "SpawnTile.h"

#include <engine/graphics/IRenderer.h>
#include <game/builders/SpriteBuilder.h>

namespace game::level::editor::ui {
SpawnTile::SpawnTile(SpawnType spawnType, const common::Vector2D<int>& position, const common::Vector2D<int>& size)
    : ITile(TileType::SPAWN, position, size)
    , m_spawnType(spawnType)
    , m_boundingBoxShape(position, size, engine::Color(0, 0, 255, 255), false)
{
    if (m_spawnType == SpawnType::CHARACTER) {
        const common::Vector2D<int> spriteDimensions(122, 146);
        auto sprite = std::make_unique<engine::Sprite>("assets/sprites/spawn_dummy.png", position,
            spriteDimensions);
        m_tileSprite = sprite.get();
        m_tileSprite->setSize({ size.x, size.y * 2 });
        m_tileSprite->setPosition({ position.x, position.y - size.y / 2 });
        m_surface.addShape(std::move(sprite));
    } else {
        game::builders::SpriteBuilder builder("assets/sprites/misc/misc.png", "assets/sprites/misc/misc.json");
        const auto map = builder.build();
        const auto& spriteResource = map.at("EquipmentSpawner").sprites.front();
        auto sprite = std::make_unique<engine::Sprite>(spriteResource.spriteSheet, spriteResource.offset, spriteResource.size, spriteResource.position);

        m_tileSprite = sprite.get();
        m_tileSprite->setSize({ size.x, size.y });
        m_tileSprite->setPosition({ position.x, position.y });
        m_surface.addShape(std::move(sprite));
    }
}

void SpawnTile::draw(const engine::IRenderer& renderer) const
{
    // always draw bounding box
    renderer.draw(m_boundingBoxShape);
    renderer.draw(*m_tileSprite);
    ITile::draw(renderer);
}

void SpawnTile::setPosition(const common::Vector2D<int>& position)
{
    ITile::setPosition(position);
    m_boundingBoxShape.setPosition(position);
    if (m_spawnType == SpawnType::CHARACTER) {
        m_tileSprite->setPosition({ position.x, position.y - m_tileSprite->size().y / 2 });
    } else {
        m_tileSprite->setPosition({ position.x, position.y });
    }
}
}
