#pragma once

#include "game/level/editor/TileType.h"

#include <engine/common/Vector2D.h>

namespace engine {
class IRenderer;
}

namespace game::level::editor::ui {

class ITile {
    TileType m_tileType;
    bool m_isSelected = false;

public:
    explicit ITile(TileType tileType)
        : m_tileType(tileType)
    {
    }

    virtual ~ITile() = default;

    virtual void draw(engine::IRenderer& renderer) = 0;
    virtual void select(bool value)
    {
        m_isSelected = value;
    }
    virtual bool isSelected() const { return m_isSelected; };
    virtual const TileType& getTileType() const { return m_tileType; }
    virtual const common::Vector2D<int>& getPosition() const = 0;
};
}