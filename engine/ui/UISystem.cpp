#include "UISystem.h"
namespace engine {
namespace ui {
    void UISystem::processInputEvent()
    {
        //TODO: key event as parameter and pass it through
        if (!m_frames.empty()) {
            Frame& currentFrame = m_frames.top();
            currentFrame.processInputEvent();
        }
    }

    void UISystem::draw(IRenderer& renderer, common::Vector2D<int> screenSize)
    {
        if (!m_frames.empty()) {
            Frame& currentFrame = m_frames.top();
            currentFrame.draw(renderer, screenSize);
        }
    }

    void UISystem::push(Frame frame)
    {
        m_frames.push(std::move(frame));
    }
}
}