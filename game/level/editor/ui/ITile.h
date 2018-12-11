#pragma once

#include <engine/common/Vector2D.h>
#include <engine/graphics/IGraphicsElement.h>
#include <engine/graphics/drawable/Sprite.h>
#include <engine/graphics/drawable/Surface.h>

#include "game/level/editor/TileType.h"
#include <game/level/LevelDomain.h>

namespace engine {
class IRenderer;
}

namespace game::level::editor::ui {

class ITile : public engine::IGraphicsElement {
    TileType m_tileType;
    bool m_isSelected = false;

protected:
    engine::Surface m_surface;
    engine::Sprite* m_tileSprite;

public:
    explicit ITile(TileType tileType, const common::Vector2D<int>& position, const common::Vector2D<int>& size)
        : m_tileType(tileType)
        , m_surface(position, size, 100)
        , m_tileSprite(nullptr)
    {
    }

    ~ITile() override = default;

    void draw(const engine::IRenderer& renderer) const override
    {
        m_surface.draw(renderer);
    }

    virtual int getAlpha() const
    {
        return m_surface.alpha();
    }

    virtual void setAlpha(int value)
    {
        m_surface.setAlpha(value);
    }

    void setTileSprite(const engine::Sprite* spriteName)
    {
        m_surface.clear();
        if (spriteName == nullptr) {
            m_tileSprite = nullptr;
        } else {
            auto sprite = std::make_unique<engine::Sprite>(
                spriteName->spritePath(), spriteName->position(), spriteName->sourceSize(), spriteName->sourcePosition());

            m_tileSprite = sprite.get();
            m_tileSprite->setSize(spriteName->size());
            m_tileSprite->setPosition(spriteName->position());

            m_surface.addShape(std::move(sprite));
        }
    }
    const engine::Sprite* getTileSprite() const
    {
        return m_tileSprite;
    }

    const common::Vector2D<int>& position() const override
    {
        return m_surface.position();
    }

    void setPosition(const common::Vector2D<int>& position) override
    {
        m_surface.setPosition(position);
        if (m_tileSprite) {
            m_tileSprite->setPosition(position);
        }
    };

    virtual void select(bool value)
    {
        m_isSelected = value;
    }

    virtual bool isSelected() const { return m_isSelected; };
    virtual const TileType& getTileType() const { return m_tileType; }
};
}