#pragma once

#include "ITile.h"

#include <engine/graphics/drawable/RectangleShape.h>
#include <engine/graphics/drawable/Sprite.h>

#include <memory>

namespace game::level::editor::ui {
class SpawnTile : public ITile {
    enum class SpawnType {
        CHARACTER,
        EQUIPMENT
    } m_spawnType{};

    engine::RectangleShape m_boundingBoxShape;
    std::unique_ptr<engine::Sprite> m_tileSprite;

public:
    SpawnTile(const common::Vector2D<int>& position, const common::Vector2D<int>& size);
    ~SpawnTile() override = default;

    void draw(engine::IRenderer& renderer) override;
    void select(bool value) override;
    const common::Vector2D<int>& getPosition() const override;
};
}