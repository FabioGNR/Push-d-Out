#include "UISystem.h"
namespace engine {
namespace ui {

    UISystem::UISystem(engine::input::InputManager& inputManager)
        : m_inputManager(inputManager)
    {
        setActive(true);
    }

    void UISystem::processInputEvent(engine::input::maps::InputMap& keyMap)
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

    void UISystem::pop()
    {
        m_frames.pop();
    }

    void UISystem::setActive(bool active)
    {
        m_active = active;
        /*
        if (!active && m_inputSubscription != nullptr) {
            m_inputSubscription->close();
            m_inputSubscription = nullptr;
        } else*/
        if (active && m_inputSubscription == nullptr) {
            subscribeInput();
        }
    }

    void UISystem::subscribeInput()
    {
        std::cout << "UISystem subs, to " << m_inputManager.connectedControllerAmount() << " controllers." << std::endl;
        m_inputSubscription = m_inputManager.subscribe([&](engine::input::maps::InputMap keymap, auto&) {
            if (m_active) {
                processInputEvent(keymap);
            }
        });

        for (size_t i = 0; i < m_inputManager.connectedControllerAmount(); i++) {
            m_inputManager.subscribe([&](engine::input::maps::InputMap keymap, auto&) {
                if (m_active) {
                    processInputEvent(keymap);
                }
            },
                i);
        }
    }
}
}