#pragma once
#include "Component.h"
#include "TextComponent.h"
#include <engine/graphics/drawable/Sprite.h>
#include <string>
#include <utility>
namespace engine {
namespace ui {
    class Image : public Component {
    protected:
        engine::Sprite m_sprite;

    public:
        Image(ComponentSize size, std::string spritePath)
            : Component(size)
            , m_sprite(spritePath, { 0, 0 }, { 0, 0 }, { 0, 0 })
        {
        }

        DrawContext draw(DrawContext context) override;
        common::Vector2D<int> calculateSize(const IRenderer& renderer, common::Vector2D<int> availableSize) const override;
    };
}
}