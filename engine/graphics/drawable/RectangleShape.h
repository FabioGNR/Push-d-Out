#pragma once

#include <graphics/Color.h>
#include <graphics/IGraphicsElement.h>
#include "common/Vector2D.h"

namespace engine {
class RectangleShape : public IGraphicsElement {
    common::Vector2D m_position;
    common::Vector2D m_size;

    Color m_color;

public:
    RectangleShape(common::Vector2D position, common::Vector2D size, const Color& color);

    void accept(IRenderVisitor& visitor) const override;

    common::Vector2D size() const;
    common::Vector2D position() const;
    const Color& color() const;

    void setSize(common::Vector2D size);
    void setPosition(common::Vector2D pos);
};
} // end namespace engine
