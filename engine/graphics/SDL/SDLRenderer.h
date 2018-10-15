#pragma once

#include <graphics/IRenderer.h>
#include <window/SDLWindow.h>

#include <memory>

struct SDL_Renderer;
namespace engine {
class SDLRenderer : public IRenderer {
    friend class SDLRenderVisitor;

    std::unique_ptr<SDL_Renderer, void (*)(SDL_Renderer*)> m_renderer;
    common::Vector2D<int> m_dimensions;

public:
    explicit SDLRenderer(const SDLWindow& window);

    void draw(const IGraphicsElement& graphicElement) const override;
    void show() override;
    void clear() override;
    double flipY(double y) const;
};
} // end namespace engine