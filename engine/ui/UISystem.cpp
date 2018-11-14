#include "UISystem.h"
namespace engine {
namespace ui {

    UISystem::UISystem(engine::input::InputManager& inputManager)
        : m_inputManager(inputManager)
    {
        setActive(true);
    }

    void UISystem::processInputEvent(engine::input::KeyMap& keyMap)
    {
        //TODO: key event as parameter and pass it through
        if (!m_frames.empty()) {
            Frame& currentFrame = m_frames.top();
            currentFrame.processInputEvent(keyMap);
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

    void UISystem::setActive(bool active)
    {
        m_active = !m_active;
        if (!active && m_inputSubscription != nullptr) {
            m_inputSubscription->close();
            m_inputSubscription = nullptr;
        } else if (active && m_inputSubscription == nullptr) {
            subscribeInput();
        }
    }

    void UISystem::subscribeInput()
    {
        m_inputSubscription = m_inputManager.subscribe([&](engine::input::KeyMap keymap, auto&) {
            processInputEvent(keymap);
        });
    }

    void UISystem::pop()
    {
        m_frames.pop();
    }
}
}