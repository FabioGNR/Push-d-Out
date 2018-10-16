#pragma once

#include <graphics/drawable/Font.h>
#include "common/Vector2D.h"

namespace engine {
class IGraphicsElement;
class IRenderer {
public:
    virtual void draw(const IGraphicsElement& graphicElement) const = 0;
    virtual void show() = 0;
    virtual void clear() = 0;
    virtual common::Vector2D<int> getFontSize(const Font& font) const = 0;
};
} // end namespace engine