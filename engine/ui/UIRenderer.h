#pragma once
#include <graphics/IRenderer.h>
#include <memory>

struct SDL_Renderer;

namespace engine {
namespace ui {
    class UIRenderer {
    public:
        explicit UIRenderer(IRenderer& renderer)
            : m_renderer{ renderer }
        {
        }
        void draw(const IGraphicsElement& element) const { m_renderer.draw(element); }

    private:
        IRenderer& m_renderer;
    };
}
}