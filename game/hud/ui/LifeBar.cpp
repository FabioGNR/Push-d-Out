#include "LifeBar.h"

#include <engine/graphics/IRenderer.h>

constexpr static const char* HEART_ALIVE = "assets/sprites/heart-0.png";
constexpr static const char* HEART_DEAD = "assets/sprites/heart-1.png";

namespace game::hud::ui {
LifeBar::LifeBar(const common::Vector2D<int>& beginPosition, int totalLifes)
    : m_beginPosition(beginPosition)
    , m_totalLifes(totalLifes)
{
    m_hearts.reserve(m_totalLifes);

    for (int i = 0; i < m_totalLifes; ++i) {
        m_hearts.push_back(std::make_unique<engine::Sprite>(
            HEART_ALIVE,
            common::Vector2D<int>(m_beginPosition.x + (40 * i), m_beginPosition.y + 20),
            common::Vector2D<int>(24, 24)));
    }
}

void LifeBar::draw(const engine::IRenderer& renderer) const
{
    for (const auto& heart : m_hearts) {
        renderer.draw(*heart);
    }
}

void LifeBar::setRemainingHearts(int lifes)
{
    for (size_t i = 0; i < m_hearts.size(); ++i) {
        if (i < static_cast<size_t>(lifes)) {
            m_hearts.at(i)->setSpritePath(HEART_ALIVE);
        } else {
            m_hearts.at(i)->setSpritePath(HEART_DEAD);
        }
    }
}
const common::Vector2D<int>& LifeBar::position() const
{
    return m_beginPosition;
}
void LifeBar::setPosition(const common::Vector2D<int>& position)
{
    m_beginPosition = position;
}
}
