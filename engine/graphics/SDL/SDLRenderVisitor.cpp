#include "SDLRenderVisitor.h"
#include "SDLRenderer.h"

#include <common/ResourceCache.h>
#include <graphics/drawable/Font.h>
#include <graphics/drawable/LineShape.h>
#include <graphics/drawable/RectangleShape.h>
#include <graphics/drawable/Sprite.h>

#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <memory>

namespace engine {
SDLRenderVisitor::SDLRenderVisitor(const SDLRenderer& renderer)
    : m_renderer(renderer)
{
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

    TTF_Font* ttfFont = nullptr;
    if (!fontCache.hasResource(font.fontPath())) {
        const auto ttf = std::shared_ptr<TTF_Font>(
            TTF_OpenFont(font.fontPath().c_str(), font.fontSize()),
            TTF_CloseFont);

        if (ttf == nullptr) {
            throw std::runtime_error(TTF_GetError());
        }
        fontCache.addResource(font.fontPath(), ttf);

        ttfFont = ttf.get();
    } else {
        ttfFont = fontCache.getResource(font.fontPath()).get();
    }

    SDL_Surface* surface = nullptr;
    SDL_Texture* texture = nullptr;
    if (!textCache.hasResource(font)) {
        SDL_Color color{
            (uint8_t)font.color().r,
            (uint8_t)font.color().g,
            (uint8_t)font.color().b,
            (uint8_t)font.color().a,
        };

        const auto surfaceMessage = std::shared_ptr<SDL_Surface>(
            TTF_RenderText_Solid(ttfFont, font.text().c_str(), color),
            SDL_FreeSurface);

        if (surfaceMessage == nullptr) {
            throw std::runtime_error(TTF_GetError());
        }

        const auto textureMessage = std::shared_ptr<SDL_Texture>(
            SDL_CreateTextureFromSurface(renderer, surfaceMessage.get()),
            SDL_DestroyTexture);

        if (textureMessage == nullptr) {
            throw std::runtime_error(TTF_GetError());
        }
        textCache.addResource(font, std::make_pair(surfaceMessage, textureMessage));

        surface = surfaceMessage.get();
        texture = textureMessage.get();
    } else {
        const auto& surfaceTexturePair = textCache.getResource(font);
        surface = surfaceTexturePair.first.get();
        texture = surfaceTexturePair.second.get();
    }

    SDL_Rect positionRect{
        font.position().x,
        font.position().y,
        surface->w,
        surface->h
    };

    SDL_RenderCopy(renderer, texture, nullptr, &positionRect);
}

void SDLRenderVisitor::visit(const Sprite& sprite)
{
    auto* renderer = m_renderer.m_renderer.get();

    SDL_Texture* texture = nullptr;

    if (!spriteCache.hasResource(sprite)) {
        const auto surfaceImage = std::shared_ptr<SDL_Surface>(
            IMG_Load(sprite.spritePath().c_str()),
            SDL_FreeSurface);

        if (surfaceImage == nullptr) {
            throw std::runtime_error(IMG_GetError());
        }

        const auto textureImage = std::shared_ptr<SDL_Texture>(
            SDL_CreateTextureFromSurface(renderer, surfaceImage.get()),
            SDL_DestroyTexture);

        if (textureImage == nullptr) {
            throw std::runtime_error(IMG_GetError());
        }

        texture = textureImage.get();
        spriteCache.addResource(sprite, std::make_pair(surfaceImage, textureImage));
    } else {
        const auto& surfaceTexturePair = spriteCache.getResource(sprite);
        texture = surfaceTexturePair.second.get();
    }

    // TODO: Do something with sprite width/height
    SDL_Rect positionRect = {
        sprite.position().x,
        sprite.position().y,
        static_cast<int>(sprite.scale().x),
        static_cast<int>(sprite.scale().y)
    };

    SDL_Rect sourceRect = {
            sprite.sourcePosition().x,
            sprite.sourcePosition().y,
            sprite.sourceSize().x,
            sprite.sourceSize().y
    };

    SDL_RenderCopy(renderer, texture, &sourceRect, &positionRect);
}

void SDLRenderVisitor::visit(const IGraphicsElement& element)
{
    (void)element;
}
} // end namespace engine
