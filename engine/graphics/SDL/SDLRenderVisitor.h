#pragma once

#include <graphics/IRenderVisitor.h>
#include <graphics/SDL/SDLRenderer.h>

namespace engine {
class SDLRenderer;
class SDLRenderVisitor : public IRenderVisitor {
    const SDLRenderer& m_renderer;

public:
    explicit SDLRenderVisitor(const SDLRenderer& renderer);

    void visit(const RectangleShape& shape) override;
    void visit(const LineShape& shape) override;
    void visit(const Font& font) override;
    void visit(const Sprite& sprite) override;
    void visit(const IGraphicsElement& element) override;
};
} // end namespace engine
