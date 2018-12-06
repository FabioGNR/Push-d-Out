#pragma once

#include "ItemBubble.h"
#include "LifeBar.h"

#include <engine/graphics/IGraphicsElement.h>
#include <engine/graphics/drawable/Font.h>
#include <engine/graphics/drawable/Surface.h>

#include <memory>

namespace game::hud::ui {
class PlayerInfo : public engine::IGraphicsElement {
private:
    const static int PRIMARY_BUBBLE_SIZE;
    const static int SECONDARY_BUBBLE_SIZE;
    const static int ITEM_BUBBLE_SIZE;

    const static common::Vector2D<double> PRIMARY_POSITION;
    const static common::Vector2D<double> PRIMARY_POSITION_FLIPPED;
    const static common::Vector2D<double> SECONDARY_POSITION;
    const static common::Vector2D<double> SECONDARY_POSITION_FLIPPED;
    const static common::Vector2D<double> ITEM_POSITION;
    const static common::Vector2D<double> ITEM_POSITION_FLIPPED;
    const static common::Vector2D<double> LIFE_POSITION;
    const static common::Vector2D<double> LIFE_POSITION_FLIPPED;
    const static common::Vector2D<double> NAME_POSITION;
    const static common::Vector2D<double> NAME_POSITION_FLIPPED;

    engine::Surface m_surface;
    bool m_flipped;

    std::string m_playerName;
    engine::Font* m_name;
    ItemBubble* m_mainItem;
    ItemBubble* m_secondaryItem;
    ItemBubble* m_tertiaryItem;
    LifeBar* m_lifeBar;

    void init();
    void initFlipped();

public:
    PlayerInfo(std::string playerName, const common::Vector2D<int>& position, const ::common::Vector2D<int>& size, bool flipped = false);
    ~PlayerInfo() override = default;

    const common::Vector2D<int>& position() const override;
    void setPosition(const common::Vector2D<int>& position) override;

    const common::Vector2D<int>& size() const;

    void draw(const engine::IRenderer& renderer) const override;
    void setRemainingLifes(int lifes);
    void setAlpha(int alpha);
};
}