#include "BackgroundSystem.h"

namespace game {
namespace systems {

    void BackgroundSystem::update(std::chrono::nanoseconds /* timeStep */)
    {
    }

    void BackgroundSystem::render(engine::IRenderer& renderer)
    {
        engine::Sprite sprite{ m_sprite, { 0, 0 }, { 0, 0 }, { 0, 0 } };
        sprite.setSize(m_screenSize);
        renderer.draw(sprite);
    }
}
}