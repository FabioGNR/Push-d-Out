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

void ItemBubble::replaceItem(std::unique_ptr<engine::Sprite> item)
{
    m_item = std::move(item);
    m_item->setPosition(common::Vector2D<int>{
        static_cast<int>(m_boundingCircle.position().x - m_boundingCircle.radius()),
        static_cast<int>(m_boundingCircle.position().y - m_boundingCircle.radius()) });
}

void ItemBubble::resetItem()
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
