#include "SDLRenderer.h"
#include "SDLRenderVisitor.h"
#include "graphics/IGraphicsElement.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <memory>

namespace engine {

SDLRenderer::SDLRenderer(const SDLWindow& window)
    : m_renderer{ nullptr, nullptr }
    , m_dimensions{ window.getDimensions().x, window.getDimensions().y }
{
    m_renderer = std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)>(
        SDL_CreateRenderer(window.m_window.get(), -1, SDL_RENDERER_ACCELERATED),
        SDL_DestroyRenderer);
    static bool isTtfInitialized = false;
    if (!isTtfInitialized) {
        if (TTF_Init() == -1) {
            throw std::runtime_error(TTF_GetError());
        }
    }

    static bool isImageInitialized = false;
    if (!isImageInitialized) {
        const auto flags = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF;
        if (((IMG_Init(flags) & flags)) == 0) {
            throw std::runtime_error(IMG_GetError());
        }
    }
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

common::Vector2D<int> SDLRenderer::getFontSize(const Font& font) const
{
    const auto ttfFont = std::unique_ptr<TTF_Font, decltype(&TTF_CloseFont)>(
        TTF_OpenFont(font.fontPath().c_str(), font.fontSize()),
        TTF_CloseFont);

    if (ttfFont == nullptr) {
        throw std::runtime_error(TTF_GetError());
    }
    int calculatedWidth = 0, calculatedHeight = 0;
    int calculationError = TTF_SizeText(ttfFont.get(), font.text().c_str(), &calculatedWidth, &calculatedHeight);
    if (calculationError != 0) {
        throw std::runtime_error(TTF_GetError());
    }
    return { calculatedWidth, calculatedHeight };
}

} // end namespace engine
