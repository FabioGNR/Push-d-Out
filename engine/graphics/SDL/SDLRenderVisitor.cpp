#include "SDLRenderVisitor.h"
#include "SDLRenderer.h"

#include <common/ResourceCache.h>
#include <graphics/drawable/Circle.h>
#include <graphics/drawable/Font.h>
#include <graphics/drawable/LineShape.h>
#include <graphics/drawable/RectangleShape.h>
#include <graphics/drawable/Sprite.h>
#include <graphics/drawable/Surface.h>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <cmath>
#include <memory>

namespace engine {
SDLRenderVisitor::SDLRenderVisitor(const SDLRenderer& renderer)
    : m_renderer(renderer)
{
}

void SDLRenderVisitor::visit(const RectangleShape& shape) const
{
    if (shape.isFilled()) {
        visitFilledRectangle(shape);
    } else {
        visitOutlinedRectangle(shape);
    }
}

void SDLRenderVisitor::visit(const LineShape& shape) const
{
    auto* renderer = m_renderer.m_renderer.get();

    SDL_SetRenderDrawColor(
        renderer,
        static_cast<Uint8>(shape.color().r),
        static_cast<Uint8>(shape.color().g),
        static_cast<Uint8>(shape.color().b),
        static_cast<Uint8>(shape.color().a));

    SDL_RenderDrawLine(renderer,
        shape.position1().x, shape.position1().y,
        shape.position2().x, shape.position2().y);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

void SDLRenderVisitor::visit(const Font& font) const
{
    if (font.text().empty()) {
        return;
    }

    auto* renderer = m_renderer.m_renderer.get();

    TTF_Font* ttfFont = nullptr;
    if (!m_renderer.fontCache.hasResource(std::make_pair(font.fontPath(), font.fontSize()))) {
        const auto ttf = std::shared_ptr<TTF_Font>(
            TTF_OpenFont(font.fontPath().c_str(), font.fontSize()),
            TTF_CloseFont);

        if (ttf == nullptr) {
            throw std::runtime_error(TTF_GetError());
        }
        m_renderer.fontCache.addResource(std::make_pair(font.fontPath(), font.fontSize()), ttf);

        ttfFont = ttf.get();
    } else {
        ttfFont = m_renderer.fontCache.getResource(std::make_pair(font.fontPath(), font.fontSize())).get();
    }

    SDL_Surface* surface = nullptr;
    SDL_Texture* texture = nullptr;
    auto* renderTarget = SDL_GetRenderTarget(renderer);
    if (!m_renderer.textCache[renderTarget].hasResource(font)) {
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

        m_renderer.textCache[renderTarget].addResource(font, std::make_pair(surfaceMessage, textureMessage));

        surface = surfaceMessage.get();
        texture = textureMessage.get();
    } else {
        const auto& surfaceTexturePair = m_renderer.textCache[renderTarget].getResource(font);
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

void SDLRenderVisitor::visit(const Sprite& sprite) const
{
    auto* renderer = m_renderer.m_renderer.get();

    SDL_Texture* texture = nullptr;
    SDL_Surface* surface = nullptr;

    if (!m_renderer.spriteCache.hasResource(sprite)) {
        const auto surfaceImage = std::shared_ptr<SDL_Surface>(
            IMG_Load(sprite.spritePath().c_str()),
            SDL_FreeSurface);

        if (surfaceImage == nullptr) {
            throw std::runtime_error(IMG_GetError());
        }
        surface = surfaceImage.get();

        const auto textureImage = std::shared_ptr<SDL_Texture>(
            SDL_CreateTextureFromSurface(renderer, surfaceImage.get()),
            SDL_DestroyTexture);

        if (textureImage == nullptr) {
            throw std::runtime_error(IMG_GetError());
        }
        texture = textureImage.get();

        m_renderer.spriteCache.addResource(sprite, std::make_pair(surfaceImage, textureImage));
    } else {
        const auto& surfaceTexturePair = m_renderer.spriteCache.getResource(sprite);
        surface = surfaceTexturePair.first.get();
        texture = surfaceTexturePair.second.get();
    }

    SDL_Rect positionRect = {
        sprite.position().x,
        sprite.position().y,
        sprite.size().x,
        sprite.size().y
    };

    common::Vector2D<int> actualSourceSize{ sprite.sourceSize() };
    if (actualSourceSize.x == 0 && actualSourceSize.y == 0) {
        actualSourceSize = common::Vector2D<int>(surface->w, surface->h);
    }

    SDL_Rect sourceRect = {
        sprite.sourcePosition().x,
        sprite.sourcePosition().y,
        actualSourceSize.x,
        actualSourceSize.y
    };

    SDL_RendererFlip rendererFlip = SDL_FLIP_NONE;
    if (sprite.isFlippedHorizontal()) {
        rendererFlip = static_cast<SDL_RendererFlip>(rendererFlip | SDL_FLIP_HORIZONTAL);
    }
    if (sprite.isFlippedVertical()) {
        rendererFlip = static_cast<SDL_RendererFlip>(rendererFlip | SDL_FLIP_VERTICAL);
    }
    if (sprite.getRotation() != 0.0) {
        const auto& relativeRotationCenter = sprite.getRotationCenter();
        common::Vector2D<int> rotationCenterPoint = { static_cast<int>(relativeRotationCenter.x * positionRect.w),
            static_cast<int>(relativeRotationCenter.y * positionRect.h) };
        if (sprite.isFlippedHorizontal()) {
            rotationCenterPoint.x = positionRect.w - rotationCenterPoint.x;
        }
        if (sprite.isFlippedVertical()) {
            rotationCenterPoint.y = positionRect.h - rotationCenterPoint.y;
        }
        SDL_Point sdlRotationCenter{ rotationCenterPoint.x, rotationCenterPoint.y };
        SDL_RenderCopyEx(renderer, texture, &sourceRect, &positionRect, sprite.getRotation(), &sdlRotationCenter, rendererFlip);
    } else {
        SDL_RenderCopyEx(renderer, texture, &sourceRect, &positionRect, 0.0, nullptr, rendererFlip);
    }
}

void SDLRenderVisitor::visit(const Circle& circle) const
{
    if (circle.fill()) { // draw the outline
        visitFilledCircle(circle);
    } else {
        visitOutlinedCircle(circle);
    }
}

void SDLRenderVisitor::visit(const Surface& surface) const
{
    auto* renderer = m_renderer.m_renderer.get();
    SDL_Texture* texture = nullptr;

    if (!m_renderer.surfaceCache.hasResource(&surface)) {
        auto textureCached = std::shared_ptr<SDL_Texture>(
            SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_TARGET,
                surface.size().x,
                surface.size().y),
            SDL_DestroyTexture);
        texture = textureCached.get();

        m_renderer.surfaceCache.addResource(&surface, textureCached);
    } else {
        texture = m_renderer.surfaceCache.getResource(&surface).get();
    }

    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    SDL_SetRenderTarget(renderer, texture);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    SDL_SetTextureAlphaMod(texture, static_cast<Uint8>(surface.alpha()));

    surface.draw(m_renderer);

    SDL_SetRenderTarget(renderer, nullptr);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    SDL_Rect rect{ surface.position().x, surface.position().y, surface.size().x, surface.size().y };
    SDL_RenderCopy(renderer, texture, nullptr, &rect);
}

void SDLRenderVisitor::visit(const IGraphicsElement& element) const
{
    // fall back
    element.draw(m_renderer);
}

void SDLRenderVisitor::visitOutlinedRectangle(const RectangleShape& shape) const
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

    SDL_RenderDrawRect(renderer, &positionRect);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
}
void SDLRenderVisitor::visitFilledRectangle(const RectangleShape& shape) const
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
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

void SDLRenderVisitor::visitFilledCircle(const Circle& circle) const
{
    auto* renderer = m_renderer.m_renderer.get();

    SDL_SetRenderDrawColor(renderer,
        static_cast<Uint8>(circle.color().r),
        static_cast<Uint8>(circle.color().g),
        static_cast<Uint8>(circle.color().b),
        static_cast<Uint8>(circle.color().a));

    const auto radius = static_cast<int>(circle.radius());
    const double radiusSquared = circle.radius() * circle.radius();
    const common::Vector2D<int> center = circle.position();

    std::vector<SDL_Rect> lines;
    SDL_Rect lineRect{ 0, 0, 1, 0 };
    for (int dx = -radius; dx <= 0; dx++) {
        // shift the vertical line to the current column
        lineRect.x = center.x + dx;
        int dxSquared = dx * dx;
        for (int dy = -radius; dy < 0; dy++) {
            if ((dxSquared + dy * dy) > radiusSquared) {
                continue; // this pixel isn't within the circle
            }
            // shift the vertical line to the starting y position
            lineRect.y = center.y + dy;
            // set the height to double the position (symmetrical)
            lineRect.h = dy * -2;
            // draw this line later
            lines.push_back(lineRect);
            // if we are not yet at the center of the circle
            if (dx != 0) {
                // then duplicate the line on the horizontal axis (symmetrical)
                lineRect.x = center.x - dx;
                lines.push_back(lineRect);
            }
            break;
        }
    }
    // send all the lines to SDL in one call
    SDL_RenderDrawRects(renderer, lines.data(), lines.size());
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

void SDLRenderVisitor::visitOutlinedCircle(const Circle& circle) const
{
    auto sides = static_cast<size_t>(2 * PI * circle.radius() / 2);

    double d_a = 2 * PI / sides, angle = d_a;
    common::Vector2D<double> end{ circle.radius(), 0.0 };
    end = end + circle.position().castTo<double>();

    for (size_t i = 0; i <= sides; ++i) {
        common::Vector2D<double> start = end;
        end.x = cos(angle) * circle.radius();
        end.y = sin(angle) * circle.radius();
        end = end + circle.position().castTo<double>();
        angle += d_a;

        visit(LineShape{ start.castTo<int>(), end.castTo<int>(), circle.color() });
    }
}

} // end namespace engine
