#pragma once

#include <engine/graphics/IGraphicsElement.h>
#include <engine/graphics/drawable/Circle.h>
#include <engine/graphics/drawable/Sprite.h>

#include <memory>

namespace game::hud::ui {
class ItemBubble : public engine::IGraphicsElement {
    engine::Circle m_boundingCircle;
    std::unique_ptr<engine::Sprite> m_item;

public:
    ItemBubble(const common::Vector2D<double>& center, double radius);
    ~ItemBubble() override = default;

    const common::Vector2D<int>& position() const override;
    void setPosition(const common::Vector2D<int>& position) override;

    void draw(const engine::IRenderer& renderer) const override;

    void replaceItem(std::unique_ptr<engine::Sprite> item);
    void resetItem();
};
}
