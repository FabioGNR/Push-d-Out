#pragma once

#include "ITile.h"

#include <engine/graphics/drawable/RectangleShape.h>
#include <engine/graphics/drawable/Sprite.h>

#include <memory>

namespace game::level::editor::ui {
class SpawnTile : public ITile {
public:
    enum class SpawnType {
        CHARACTER,
        EQUIPMENT
    } m_spawnType{};

private:
    engine::RectangleShape m_boundingBoxShape;

public:
    SpawnTile(SpawnType spawnType, const common::Vector2D<int>& position, const common::Vector2D<int>& size);
    ~SpawnTile() override = default;

    SpawnType getSpawnType() const { return m_spawnType; }

    void draw(const engine::IRenderer& renderer) const override;
    void setPosition(const common::Vector2D<int>& position) override;
};
}
