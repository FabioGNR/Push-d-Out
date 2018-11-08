#pragma once

#include "engine/common/Vector2D.h"
#include "engine/graphics/Color.h"
#include "engine/graphics/IGraphicsElement.h"

namespace engine {
class RectangleShape : public IGraphicsElement {
    common::Vector2D<int> m_position;
    common::Vector2D<int> m_size;

    Color m_color;

public:
    RectangleShape(common::Vector2D<int> position, common::Vector2D<int> size, const Color& color);
    virtual ~RectangleShape() = default;

    void accept(IRenderVisitor& visitor) const override;

    common::Vector2D<int> size() const;
    common::Vector2D<int> position() const;
    const Color& color() const;

    void setSize(common::Vector2D<int> size);
    void setPosition(common::Vector2D<int> position);
};
} // end namespace engine
