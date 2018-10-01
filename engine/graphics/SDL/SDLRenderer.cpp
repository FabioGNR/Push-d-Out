#include "SDLRenderer.h"
#include "SDLRenderVisitor.h"
#include "graphics/IGraphicsElement.h"

#include <SDL.h>

namespace engine {

SDLRenderer::SDLRenderer(const SDLWindow& window)
    : m_renderer{ nullptr, nullptr }
{
    m_renderer = std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)>(
        SDL_CreateRenderer(window.m_window.get(), -1, SDL_RENDERER_ACCELERATED),
        SDL_DestroyRenderer);
}

void SDLRenderer::draw(const IGraphicsElement& graphicElement) const
{
    SDLRenderVisitor visitor(*this);
    graphicElement.accept(visitor);
}

void SDLRenderer::show()
{
    SDL_RenderPresent(m_renderer.get());
}

void SDLRenderer::clear()
{
    SDL_RenderClear(m_renderer.get());
}

} // end namespace engine
