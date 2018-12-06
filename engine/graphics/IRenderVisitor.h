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
    virtual void visit(const RectangleShape&) const = 0;
    virtual void visit(const LineShape&) const = 0;
    virtual void visit(const Font&) const = 0;
    virtual void visit(const Sprite&) const = 0;
    virtual void visit(const Circle&) const = 0;
    virtual void visit(const Surface&) const = 0;
    virtual void visit(const IGraphicsElement&) const = 0;
};
} // end namespace visitor
