#include "PlayerName.h"

namespace game::hud::ui {

void PlayerName::draw(const engine::IRenderer& renderer) const
{
    for (const auto& sprite : m_sprites) {
        renderer.draw(sprite);
    }
}

const common::Vector2D<int>& PlayerName::position() const
{
    return m_beginPosition;
}

void PlayerName::setPosition(const common::Vector2D<int>& position)
{
    m_beginPosition = position;
}
}
