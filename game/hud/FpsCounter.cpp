#include "FpsCounter.h"
#include <engine/graphics/drawable/RectangleShape.h>

namespace game {
namespace hud {
    FpsCounter::FpsCounter()
    {
        m_last = std::chrono::high_resolution_clock::now();
    }

    void FpsCounter::render(engine::IRenderer& renderer)
    {
        ++m_count;
        auto duration = std::chrono::high_resolution_clock::now() - m_last;
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(duration);

        if (ms.count() >= 1000) {
            m_displayCount = m_count;
            m_count = 0;
            m_last = std::chrono::high_resolution_clock::now();
        }

        engine::Font font{ "assets/fonts/8bit.ttf", std::to_string(m_displayCount), 12, engine::Color{ 0, 0, 0 },
            common::Vector2D(5, 5) };

        auto size = renderer.getFontSize(font);
        size.y += 6;
        size.x += 8;

        renderer.draw(engine::RectangleShape{ common::Vector2D{ 0, 0 }, size, engine::Color{ 255, 255, 0 } });
        renderer.draw(font);
    }
}
}
