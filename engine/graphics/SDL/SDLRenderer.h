#pragma once

#include "engine/graphics/IRenderer.h"
#include "engine/window/SDLWindow.h"

#include <engine/common/ResourceCache.h>
#include <memory>

struct SDL_Renderer;
struct SDL_Texture;
struct SDL_Surface;
typedef struct _TTF_Font TTF_Font;

namespace engine {

using SurfaceTexturePair = std::pair<std::shared_ptr<SDL_Surface>, std::shared_ptr<SDL_Texture>>;
static common::ResourceCache<std::string, std::shared_ptr<TTF_Font>> fontCache;
static common::ResourceCache<Font, SurfaceTexturePair> textCache;
static common::ResourceCache<Sprite, SurfaceTexturePair> spriteCache;

class SDLRenderer : public IRenderer {
    friend class SDLRenderVisitor;

    std::unique_ptr<SDL_Renderer, void (*)(SDL_Renderer*)> m_renderer;
    common::Vector2D<int> m_dimensions;

public:
    explicit SDLRenderer(const SDLWindow& window);

    SDLRenderer(const SDLRenderer& other) = delete;
    SDLRenderer& operator=(const SDLRenderer& other) = delete;

    SDLRenderer(SDLRenderer&& other) = delete;
    SDLRenderer& operator=(SDLRenderer&& other) = delete;

    ~SDLRenderer() override = default;

    void draw(const IGraphicsElement& graphicElement) const override;
    void show() override;
    void clear() override;

    common::Vector2D<int> getFontSize(const Font& font) const override;
    common::Vector2D<int> getSpriteSize(const Sprite& sprite) const override;
};
} // end namespace engine