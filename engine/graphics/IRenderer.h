#pragma once

#include "engine/common/Vector2D.h"
#include "engine/graphics/drawable/Font.h"

namespace engine {
class IGraphicsElement;
class IRenderer {
public:
    IRenderer() = default;

    IRenderer(const IRenderer& other) = default;
    IRenderer& operator=(const IRenderer& other) = default;

    IRenderer(IRenderer&& other) = default;
    IRenderer& operator=(IRenderer&& other) = default;

    virtual ~IRenderer() = default;

    virtual void draw(const IGraphicsElement& graphicElement) const = 0;
    virtual void show() = 0;
    virtual void clear() = 0;
    virtual common::Vector2D<int> getFontSize(const Font& font) const = 0;
};
} // end namespace engine