#pragma once

#include "IRenderVisitor.h"
#include "engine/common/Vector2D.h"

namespace engine {
class IRenderer;

class IGraphicsElement {
public:
    virtual ~IGraphicsElement() = default;
    virtual void draw(const IRenderer& renderer) const = 0;

    virtual const common::Vector2D<int>& position() const = 0;
    virtual void setPosition(const common::Vector2D<int>& position) = 0;

    virtual void accept(const IRenderVisitor& visitor) const
    {
        visitor.visit(*this);
    }
};

} // end namespace engine
