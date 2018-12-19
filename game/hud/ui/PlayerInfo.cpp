#include "PlayerInfo.h"

#include <engine/ecs/Entity.h>
#include <engine/ecs/World.h>
#include <engine/graphics/IRenderer.h>
#include <game/components/InventoryComponent.h>
#include <game/components/SpriteComponent.h>

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
const common::Vector2D<double> PlayerInfo::NAME_POSITION = common::Vector2D<double>(130, 120);
const common::Vector2D<double> PlayerInfo::NAME_POSITION_FLIPPED = common::Vector2D<double>(220, 120);

PlayerInfo::PlayerInfo(engine::ecs::Entity* entity, const std::string& playerName, PlayerName::Color color, const common::Vector2D<int>& position, const ::common::Vector2D<int>& size, bool flipped)
    : m_surface(position, size, 255)
    , m_flipped(flipped)
    , m_primarySlot(nullptr)
    , m_secondarySlot(nullptr)
    , m_itemSlot(nullptr)
    , m_lifeBar(nullptr)
    , m_player(entity)
{
    if (m_flipped) {
        initFlipped(playerName, color);
    } else {
        init(playerName, color);
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

void PlayerInfo::init(const std::string& name, PlayerName::Color color)
{
    auto playerName = std::make_unique<PlayerName>(
        name,
        color,
        PlayerInfo::NAME_POSITION.castTo<int>(),
        common::Vector2D<int>{ 64, 64 });
    m_playerName = playerName.get();
    m_surface.addShape(std::move(playerName));

    auto primarySlot = std::make_unique<ItemBubble>(
        PlayerInfo::PRIMARY_POSITION,
        PlayerInfo::PRIMARY_BUBBLE_SIZE);
    m_primarySlot = primarySlot.get();
    m_surface.addShape(std::move(primarySlot));

    auto secondarySlot = std::make_unique<ItemBubble>(
        PlayerInfo::SECONDARY_POSITION,
        PlayerInfo::SECONDARY_BUBBLE_SIZE);
    m_secondarySlot = secondarySlot.get();
    m_surface.addShape(std::move(secondarySlot));

    auto itemSlot = std::make_unique<ItemBubble>(
        PlayerInfo::ITEM_POSITION,
        PlayerInfo::ITEM_BUBBLE_SIZE);
    m_itemSlot = itemSlot.get();
    m_surface.addShape(std::move(itemSlot));

    auto lifeBar = std::make_unique<LifeBar>(
        PlayerInfo::LIFE_POSITION.castTo<int>(),
        3);
    m_lifeBar = lifeBar.get();
    m_surface.addShape(std::move(lifeBar));
}

void PlayerInfo::initFlipped(const std::string& name, PlayerName::Color color)
{
    auto width = m_surface.size().x;

    auto playerName = std::make_unique<PlayerName>(
        name,
        color,
        common::Vector2D(width - PlayerInfo::NAME_POSITION_FLIPPED.x, PlayerInfo::NAME_POSITION_FLIPPED.y).castTo<int>(),
        common::Vector2D<int>{ 64, 64 });
    m_playerName = playerName.get();
    m_surface.addShape(std::move(playerName));

    auto primarySlot = std::make_unique<ItemBubble>(
        common::Vector2D(width - PlayerInfo::PRIMARY_POSITION_FLIPPED.x, PlayerInfo::PRIMARY_POSITION_FLIPPED.y),
        PlayerInfo::PRIMARY_BUBBLE_SIZE);
    m_primarySlot = primarySlot.get();
    m_surface.addShape(std::move(primarySlot));

    auto secondarySlot = std::make_unique<ItemBubble>(
        common::Vector2D(width - PlayerInfo::SECONDARY_POSITION_FLIPPED.x, PlayerInfo::SECONDARY_POSITION_FLIPPED.y),
        PlayerInfo::SECONDARY_BUBBLE_SIZE);
    m_secondarySlot = secondarySlot.get();
    m_surface.addShape(std::move(secondarySlot));

    auto itemSlot = std::make_unique<ItemBubble>(
        common::Vector2D(width - PlayerInfo::ITEM_POSITION_FLIPPED.x, PlayerInfo::ITEM_POSITION_FLIPPED.y),
        PlayerInfo::ITEM_BUBBLE_SIZE);
    m_itemSlot = itemSlot.get();
    m_surface.addShape(std::move(itemSlot));

    auto lifeBar = std::make_unique<LifeBar>(
        common::Vector2D(width - PlayerInfo::LIFE_POSITION_FLIPPED.x, PlayerInfo::LIFE_POSITION_FLIPPED.y).castTo<int>(),
        3);
    m_lifeBar = lifeBar.get();
    m_surface.addShape(std::move(lifeBar));
}

void PlayerInfo::update(engine::ecs::World& world)
{
    auto& inv = world.getComponent<components::InventoryComponent>(*m_player);

    updateEquipment(world, inv.activeEquipment.get(), m_primarySlot);
    updateEquipment(world, inv.otherEquipment.get(), m_secondarySlot);
    updateEquipment(world, inv.item.get(), m_itemSlot);
}

void PlayerInfo::updateEquipment(engine::ecs::World& world, engine::ecs::Entity* entity, ItemBubble* bubble)
{
    if (entity == nullptr || !entity->hasComponent<components::SpriteComponent>()) {
        bubble->clear();
        return;
    }

    auto& sprite = world.getComponent<components::SpriteComponent>(*entity);
    auto resource = sprite.sprites.at(0);
    bubble->set(std::make_unique<engine::Sprite>(resource.spriteSheet,
        resource.offset,
        resource.size,
        resource.position));
}
}
