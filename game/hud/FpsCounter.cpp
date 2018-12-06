#include "FpsCounter.h"

#include <engine/graphics/drawable/RectangleShape.h>

namespace game::hud {
FpsCounter::FpsCounter(const common::Vector2D<int>& position)
    : m_last(std::chrono::high_resolution_clock::now())
    , m_font{
        "assets/fonts/8bit.ttf",
        "0",
        12,
        engine::Color{ 0, 0, 0 },
        common::Vector2D(5, 5)
    }
    , m_position(position)
{
}

void FpsCounter::draw(const engine::IRenderer& renderer) const
{
    ++m_count;
    const auto duration = std::chrono::high_resolution_clock::now() - m_last;
    const auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(duration);

    if (ms.count() >= 1000) {
        m_displayCount = m_count;
        m_count = 0;
        m_last = std::chrono::high_resolution_clock::now();
        m_font.setText(std::to_string(m_displayCount));
    }

    auto size = renderer.getFontSize(m_font);
    size.y += 6;
    size.x += 8;

    renderer.draw(engine::RectangleShape{ m_position, size, engine::Color{ 255, 255, 0 } });
    renderer.draw(m_font);
}

const common::Vector2D<int>& FpsCounter::position() const
{
    return m_position;
}

void FpsCounter::setPosition(const common::Vector2D<int>& position)
{
    m_position = position;
}
}
