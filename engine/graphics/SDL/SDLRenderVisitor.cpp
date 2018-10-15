#include "SDLRenderVisitor.h"
#include "SDLRenderer.h"

#include <graphics/drawable/Font.h>
#include <graphics/drawable/LineShape.h>
#include <graphics/drawable/RectangleShape.h>
#include <graphics/drawable/Sprite.h>

#include <SDL_image.h>
#include <SDL_ttf.h>
#include <memory>

namespace engine {

SDLRenderVisitor::SDLRenderVisitor(const SDLRenderer& renderer)
    : m_renderer(renderer)
{
    static bool isTtfInitialized = false;
    if (!isTtfInitialized) {
        if (TTF_Init() == -1) {
            throw std::runtime_error(TTF_GetError());
        }
    }

    static bool isImageInitialized = false;
    if (!isImageInitialized) {
        const int flags = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF;
        if (!(IMG_Init(flags) & flags)) {
            throw std::runtime_error(IMG_GetError());
        }
    }
}

void SDLRenderVisitor::visit(const RectangleShape& shape)
{
    auto* renderer = m_renderer.m_renderer.get();

    SDL_SetRenderDrawColor(renderer,
        (uint8_t)(shape.color().r),
        (uint8_t)(shape.color().g),
        (uint8_t)(shape.color().b),
        (uint8_t)(shape.color().a));

    SDL_Rect positionRect{
        shape.position().x,
        shape.position().y,
        shape.size().x,
        shape.size().y
    };

    SDL_RenderFillRect(renderer, &positionRect);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
}

void SDLRenderVisitor::visit(const LineShape& shape)
{
    auto* renderer = m_renderer.m_renderer.get();

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
    SDL_RenderDrawLine(renderer,
        shape.position1().x, shape.position1().y,
        shape.position2().x, shape.position2().y);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
}

void SDLRenderVisitor::visit(const Font& font)
{
    auto* renderer = m_renderer.m_renderer.get();
    const auto ttfFont = std::unique_ptr<TTF_Font, decltype(&TTF_CloseFont)>(
        TTF_OpenFont(font.fontPath().c_str(), font.fontSize()),
        TTF_CloseFont);

    if (ttfFont == nullptr) {
        throw std::runtime_error(TTF_GetError());
    }

    SDL_Color color{
        (uint8_t)(font.color().r),
        (uint8_t)(font.color().g),
        (uint8_t)(font.color().b),
        (uint8_t)(font.color().a),
    };

    const auto surfaceMessage = std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)>(
        TTF_RenderText_Solid(ttfFont.get(), font.text().c_str(), color),
        SDL_FreeSurface);

    if (surfaceMessage == nullptr) {
        throw std::runtime_error(TTF_GetError());
    }

    const auto textureMessage = std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)>(
        SDL_CreateTextureFromSurface(renderer, surfaceMessage.get()),
        SDL_DestroyTexture);

    if (textureMessage == nullptr) {
        throw std::runtime_error(TTF_GetError());
    }

    SDL_Rect positionRect{
        font.position().x,
        font.position().y,
        surfaceMessage->w,
        surfaceMessage->h
    };

    SDL_RenderCopy(renderer, textureMessage.get(), nullptr, &positionRect);
}

void SDLRenderVisitor::visit(const Sprite& sprite)
{
    auto* renderer = m_renderer.m_renderer.get();

    const auto surfaceImage = std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)>(
        IMG_Load(sprite.spritePath().c_str()),
        SDL_FreeSurface);

    if (surfaceImage == nullptr) {
        throw std::runtime_error(IMG_GetError());
    }

    const auto textureImage = std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)>(
        SDL_CreateTextureFromSurface(renderer, surfaceImage.get()),
        SDL_DestroyTexture);

    if (textureImage == nullptr) {
        throw std::runtime_error(IMG_GetError());
    }

    // TODO: Do something with sprite width/height
    SDL_Rect positionRect = {
        sprite.position().x,
        sprite.position().y,
        (int)(surfaceImage->w * sprite.scale()),
        (int)(surfaceImage->h * sprite.scale())
    };

    SDL_RenderCopy(renderer, textureImage.get(), nullptr, &positionRect);
}

void SDLRenderVisitor::visit(const IGraphicsElement& element)
{
    (void)element;
}
} // end namespace engine
