#pragma once
#include "Frame.h"
#include "UIRenderer.h"
#include <stack>

namespace engine {
namespace ui {

    class UISystem {
    public:
        void draw(UIRenderer& renderer, common::Vector2D screenSize);
        void push(Frame frame);
        void processInputEvent();

    private:
        std::stack<Frame> m_frames;
    };
}
}