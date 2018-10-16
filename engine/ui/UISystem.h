#pragma once
#include "Frame.h"
#include "graphics/IRenderer.h"
#include <stack>

namespace engine {
namespace ui {

    class UISystem {
    public:
        void draw(IRenderer& renderer, common::Vector2D<int> screenSize);
        void push(Frame frame);
        void processInputEvent();

    private:
        std::stack<Frame> m_frames;
    };
}
}