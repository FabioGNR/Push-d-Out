#pragma once

#include <engine/common/Vector2D.h>
#include <engine/graphics/IGraphicsElement.h>

#include "game/level/editor/TileType.h"

namespace engine {
class IRenderer;
}

namespace game::level::editor::ui {

class ITile : public engine::IGraphicsElement {
    TileType m_tileType;
    bool m_isSelected = false;

public:
    explicit ITile(TileType tileType)
        : m_tileType(tileType)
    {
    }

    ~ITile() override = default;

    void draw(const engine::IRenderer& renderer) const override = 0;
    const common::Vector2D<int>& position() const override = 0;
    void setPosition(const common::Vector2D<int>& position) override = 0;

    virtual void select(bool value)
    {
        m_isSelected = value;
    }
    virtual bool isSelected() const { return m_isSelected; };
    virtual const TileType& getTileType() const { return m_tileType; }
};
}