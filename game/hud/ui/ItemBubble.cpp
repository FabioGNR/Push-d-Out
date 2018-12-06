#include "ItemBubble.h"
#include <engine/graphics/IRenderer.h>

namespace game::hud::ui {

ItemBubble::ItemBubble(const common::Vector2D<double>& center, double radius)
    : m_boundingCircle(center, radius, engine::Color{ 255, 255, 255, 255 }, true)
    , m_item(nullptr)
{
}

void ItemBubble::draw(const engine::IRenderer& renderer) const
{
    renderer.draw(m_boundingCircle);

    if (m_item != nullptr) {
        renderer.draw(*m_item);
    }
}

void ItemBubble::set(std::unique_ptr<engine::Sprite> item)
{
    m_item = std::move(item);
    auto ratio = m_item->size().x / m_item->size().y;
    m_item->setSize(common::Vector2D<int>{
        static_cast<int>(m_boundingCircle.radius() * ratio * 0.8),
        static_cast<int>(m_boundingCircle.radius() * 0.8) });
    m_item->setPosition(common::Vector2D<int>{
        static_cast<int>(m_boundingCircle.position().x - (m_item->size().x / 2)),
        static_cast<int>(m_boundingCircle.position().y - (m_item->size().y / 2)) });
}

void ItemBubble::clear()
{
    m_item = nullptr;
}

const common::Vector2D<int>& ItemBubble::position() const
{
    return m_boundingCircle.position();
}

void ItemBubble::setPosition(const common::Vector2D<int>& position)
{
    m_boundingCircle.setPosition(position);
}
}
