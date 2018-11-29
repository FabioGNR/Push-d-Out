#pragma once

#include "engine/graphics/IRenderer.h"
#include "engine/window/SDLWindow.h"
#include <engine/common/ResourceCache.h>
#include <engine/graphics/drawable/Surface.h>
#include <memory>

struct SDL_Renderer;
struct SDL_Texture;
struct SDL_Surface;
typedef struct _TTF_Font TTF_Font;

namespace engine {

class SDLRenderer : public IRenderer {
    friend class SDLRenderVisitor;

    std::unique_ptr<SDL_Renderer, void (*)(SDL_Renderer*)> m_renderer;
    common::Vector2D<int> m_dimensions;

    using SurfaceTexturePair = std::pair<std::shared_ptr<SDL_Surface>, std::shared_ptr<SDL_Texture>>;
    using FontFontsizePair = std::pair<std::string, int>;
    mutable common::ResourceCache<FontFontsizePair, std::shared_ptr<TTF_Font>> fontCache;
    mutable common::ResourceCache<Font, SurfaceTexturePair> textCache;
    mutable common::ResourceCache<Sprite, SurfaceTexturePair> spriteCache;
    mutable common::ResourceCache<Surface, std::shared_ptr<SDL_Texture>> surfaceCache;

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
    void setBlendMode(engine::graphics::BlendModes) override;
    common::Vector2D<int> getSpriteSize(const Sprite& sprite) const override;
};
} // end namespace engine