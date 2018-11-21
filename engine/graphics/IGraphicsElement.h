#pragma once

namespace engine {
class IRenderVisitor;

class IGraphicsElement {
public:
    virtual ~IGraphicsElement() = default;
    virtual void accept(IRenderVisitor& visitor) const = 0;
    virtual ~IGraphicsElement() = default;
};
} // end namespace engine
