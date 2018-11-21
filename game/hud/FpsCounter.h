#pragma once

#include <chrono>
#include <engine/graphics/IRenderer.h>

namespace game {
namespace hud {
    class FpsCounter {
    private:
        int m_count = 0;
        int m_displayCount = 0;
        std::chrono::time_point<std::chrono::high_resolution_clock> m_last;

    public:
        FpsCounter();
        ~FpsCounter() = default;

        void render(engine::IRenderer&);
    };
}
}
