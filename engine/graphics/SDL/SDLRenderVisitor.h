#pragma once

#include <graphics/IRenderVisitor.h>
#include <graphics/SDL/SDLRenderer.h>

namespace engine {
class SDLRenderer;
class SDLRenderVisitor : public IRenderVisitor {
    const SDLRenderer& m_renderer;

public:
    explicit SDLRenderVisitor(const SDLRenderer& renderer);
    ~SDLRenderVisitor() override = default;

    void visit(const RectangleShape& shape) override;
    void visit(const LineShape& shape) override;
    void visit(const Font& font) override;
    void visit(const Sprite& sprite) override;
    void visit(const Circle& circle) override;
    void visit(const Surface& surface) override;
    void visit(const IGraphicsElement& element) override;

private:
    void visitOutlinedCircle(const Circle& circle);
    void visitFilledCircle(const Circle& circle) const;
    void visitFilledRectangle(const RectangleShape& shape) const;
    void visitOutlinedRectangle(const RectangleShape& shape) const;
};
} // end namespace engine
