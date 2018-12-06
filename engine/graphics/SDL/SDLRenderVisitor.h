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

    void visit(const RectangleShape& shape) const override;
    void visit(const LineShape& shape) const override;
    void visit(const Font& font) const override;
    void visit(const Sprite& sprite) const override;
    void visit(const Circle& circle) const override;
    void visit(const Surface& surface) const override;
    void visit(const IGraphicsElement& element) const override;

private:
    void visitOutlinedCircle(const Circle& circle) const;
    void visitFilledCircle(const Circle& circle) const;
    void visitFilledRectangle(const RectangleShape& shape) const;
    void visitOutlinedRectangle(const RectangleShape& shape) const;
};
} // end namespace engine
