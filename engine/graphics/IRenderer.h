#pragma once

namespace engine {
class IGraphicsElement;
class IRenderer {
public:
    virtual void draw(const IGraphicsElement& graphicElement) const = 0;
    virtual void show() = 0;
    virtual void clear() = 0;
};
} // end namespace engine