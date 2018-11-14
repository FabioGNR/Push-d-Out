#pragma once
#include "Frame.h"

#include <engine/graphics/IRenderer.h>
#include <engine/input/InputManager.h>
#include <engine/input/KeyMap.h>

#include <stack>

namespace engine {
namespace ui {

    class UISystem {
    public:
        explicit UISystem(engine::input::InputManager& inputManager);
        void draw(IRenderer& renderer, common::Vector2D<int> screenSize);
        void push(Frame frame);
        void pop();
        void processInputEvent(engine::input::KeyMap& keyMap);
        void setActive(bool active);

    private:
        std::stack<Frame> m_frames;
        bool m_active = true;
        engine::input::InputManager& m_inputManager;
        std::shared_ptr<engine::events::Subscription<engine::input::KeyMap>> m_inputSubscription;

        void subscribeInput();
    };
}
}