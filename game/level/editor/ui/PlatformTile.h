#pragma once

#include "ITile.h"
#include "TileSet.h"

#include <engine/common/Vector2D.h>
#include <engine/graphics/drawable/RectangleShape.h>
#include <engine/graphics/drawable/Sprite.h>

#include <memory>

namespace game::level::editor::ui {
class PlatformTile : public ITile {
    engine::RectangleShape m_boundingBoxShape;

    std::unique_ptr<engine::Sprite> m_tileSprite;

public:
    PlatformTile(const common::Vector2D<int>& position, const common::Vector2D<int>& size);
    ~PlatformTile() override = default;

    void draw(engine::IRenderer& renderer) override;
    void select(bool value) override;
    const common::Vector2D<int>& getPosition() const override;

    void setTileSprite(const std::string& spriteName);
    const engine::Sprite* getTileSprite() const;
};
}
