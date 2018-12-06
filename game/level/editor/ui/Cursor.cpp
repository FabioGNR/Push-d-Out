#include "Cursor.h"

#include <engine/graphics/IRenderer.h>

namespace game::level::editor::ui {

Cursor::Cursor(const std::string& cursorSprite)
    : m_cursorSprite(cursorSprite, { 0, 0 }, { 30, 30 })
{
}

void Cursor::setPosition(const common::Vector2D<int>& position)
{
    m_cursorSprite.setPosition(position);
}

void Cursor::draw(const engine::IRenderer& renderer) const
{
    renderer.draw(m_cursorSprite);
}

const common::Vector2D<int>& Cursor::position() const
{
    return m_cursorSprite.position();
}
} // end namespace
