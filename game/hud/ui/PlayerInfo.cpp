#include "PlayerInfo.h"

#include <engine/graphics/IRenderer.h>

namespace game::hud::ui {

const int PlayerInfo::PRIMARY_BUBBLE_SIZE = 50;
const int PlayerInfo::SECONDARY_BUBBLE_SIZE = 30;
const int PlayerInfo::ITEM_BUBBLE_SIZE = 25;

const common::Vector2D<double> PlayerInfo::PRIMARY_POSITION = common::Vector2D<double>(80, 100);
const common::Vector2D<double> PlayerInfo::PRIMARY_POSITION_FLIPPED = common::Vector2D<double>(80, 100);
const common::Vector2D<double> PlayerInfo::SECONDARY_POSITION = common::Vector2D<double>(60, 50);
const common::Vector2D<double> PlayerInfo::SECONDARY_POSITION_FLIPPED = common::Vector2D<double>(60, 50);
const common::Vector2D<double> PlayerInfo::ITEM_POSITION = common::Vector2D<double>(150, 80);
const common::Vector2D<double> PlayerInfo::ITEM_POSITION_FLIPPED = common::Vector2D<double>(150, 80);
const common::Vector2D<double> PlayerInfo::LIFE_POSITION = common::Vector2D<double>(120, 0);
const common::Vector2D<double> PlayerInfo::LIFE_POSITION_FLIPPED = common::Vector2D<double>(220, 0);
const common::Vector2D<double> PlayerInfo::NAME_POSITION = common::Vector2D<double>(150, 120);
const common::Vector2D<double> PlayerInfo::NAME_POSITION_FLIPPED = common::Vector2D<double>(200, 120);

PlayerInfo::PlayerInfo(std::string playerName, const common::Vector2D<int>& position, const ::common::Vector2D<int>& size, bool flipped)
    : m_surface(position, size, 255)
    , m_flipped(flipped)
    , m_playerName(std::move(playerName))
    , m_name(nullptr)
    , m_mainItem(nullptr)
    , m_secondaryItem(nullptr)
    , m_tertiaryItem(nullptr)
    , m_lifeBar(nullptr)
{
    if (flipped) {
        initFlipped();
    } else {
        init();
    }
}

void PlayerInfo::draw(const engine::IRenderer& renderer) const
{
    renderer.draw(m_surface);
}

void PlayerInfo::setRemainingLifes(int lifes)
{
    m_lifeBar->setRemainingHearts(lifes);
}

void PlayerInfo::setAlpha(int alpha)
{
    m_surface.setAlpha(alpha);
}
const common::Vector2D<int>& PlayerInfo::position() const
{
    return m_surface.position();
}
void PlayerInfo::setPosition(const common::Vector2D<int>& position)
{
    m_surface.setPosition(position);
}

const common::Vector2D<int>& PlayerInfo::size() const
{
    return m_surface.size();
}

void PlayerInfo::init()
{
    auto name = std::make_unique<engine::Font>(
        "assets/fonts/8bit.ttf",
        m_playerName,
        24,
        engine::Color(255, 255, 255, 255),
        PlayerInfo::NAME_POSITION.castTo<int>());
    m_name = name.get();
    m_surface.addShape(std::move(name));

    auto primarySlot = std::make_unique<ItemBubble>(
        PlayerInfo::PRIMARY_POSITION,
        PlayerInfo::PRIMARY_BUBBLE_SIZE);
    m_mainItem = primarySlot.get();
    m_surface.addShape(std::move(primarySlot));

    auto secondarySlot = std::make_unique<ItemBubble>(
        PlayerInfo::SECONDARY_POSITION,
        PlayerInfo::SECONDARY_BUBBLE_SIZE);
    m_secondaryItem = secondarySlot.get();
    m_surface.addShape(std::move(secondarySlot));

    auto itemSlot = std::make_unique<ItemBubble>(
        PlayerInfo::ITEM_POSITION,
        PlayerInfo::ITEM_BUBBLE_SIZE);
    m_tertiaryItem = itemSlot.get();
    m_surface.addShape(std::move(itemSlot));

    auto lifeBar = std::make_unique<LifeBar>(
        PlayerInfo::LIFE_POSITION.castTo<int>(),
        3);
    m_lifeBar = lifeBar.get();
    m_surface.addShape(std::move(lifeBar));
}

void PlayerInfo::initFlipped()
{
    auto width = m_surface.size().x;

    auto name = std::make_unique<engine::Font>(
        "assets/fonts/8bit.ttf",
        m_playerName,
        24,
        engine::Color(255, 255, 255, 255),
        common::Vector2D(width - PlayerInfo::NAME_POSITION_FLIPPED.x, PlayerInfo::NAME_POSITION_FLIPPED.y).castTo<int>());
    m_name = name.get();
    m_surface.addShape(std::move(name));

    auto primarySlot = std::make_unique<ItemBubble>(
        common::Vector2D(width - PlayerInfo::PRIMARY_POSITION_FLIPPED.x, PlayerInfo::PRIMARY_POSITION_FLIPPED.y),
        PlayerInfo::PRIMARY_BUBBLE_SIZE);
    m_mainItem = primarySlot.get();
    m_surface.addShape(std::move(primarySlot));

    auto secondarySlot = std::make_unique<ItemBubble>(
        common::Vector2D(width - PlayerInfo::SECONDARY_POSITION_FLIPPED.x, PlayerInfo::SECONDARY_POSITION_FLIPPED.y),
        PlayerInfo::SECONDARY_BUBBLE_SIZE);
    m_secondaryItem = secondarySlot.get();
    m_surface.addShape(std::move(secondarySlot));

    auto itemSlot = std::make_unique<ItemBubble>(
        common::Vector2D(width - PlayerInfo::ITEM_POSITION_FLIPPED.x, PlayerInfo::ITEM_POSITION_FLIPPED.y),
        PlayerInfo::ITEM_BUBBLE_SIZE);
    m_tertiaryItem = itemSlot.get();
    m_surface.addShape(std::move(itemSlot));

    auto lifeBar = std::make_unique<LifeBar>(
        common::Vector2D(width - PlayerInfo::LIFE_POSITION_FLIPPED.x, PlayerInfo::LIFE_POSITION_FLIPPED.y).castTo<int>(),
        3);
    m_lifeBar = lifeBar.get();
    m_surface.addShape(std::move(lifeBar));
}
}
