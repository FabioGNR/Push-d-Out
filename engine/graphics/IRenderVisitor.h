#pragma once

namespace engine {
class IGraphicsElement;
class RectangleShape;
class LineShape;
class Font;
class Sprite;
class Circle;
class Surface;

class IRenderVisitor {
public:
    virtual ~IRenderVisitor() = default;
    virtual void visit(const RectangleShape&) = 0;
    virtual void visit(const LineShape&) = 0;
    virtual void visit(const Font&) = 0;
    virtual void visit(const Sprite&) = 0;
    virtual void visit(const Circle&) = 0;
    virtual void visit(const Surface&) = 0;
    virtual void visit(const IGraphicsElement&) = 0;
};
} // end namespace visitor
