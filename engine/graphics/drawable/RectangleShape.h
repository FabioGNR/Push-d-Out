#pragma once

#include "engine/common/Vector2D.h"
#include "engine/graphics/Color.h"
#include "engine/graphics/IGraphicsElement.h"

namespace engine {
class RectangleShape : public IGraphicsElement {
    common::Vector2D<int> m_position;
    common::Vector2D<int> m_size;

    bool m_fill;

    Color m_color;

public:
    RectangleShape(common::Vector2D<int> position, common::Vector2D<int> size, const Color& color, bool fill = true);

    ~RectangleShape() override = default;

    void accept(IRenderVisitor& visitor) const override;

    const common::Vector2D<int>& size() const;
    const common::Vector2D<int>& position() const;
    const Color& color() const;
    bool isFilled() const;

    void setColor(const Color& color);
    void setSize(const common::Vector2D<int>& size);
    void setPosition(const common::Vector2D<int>& position);
    void setFill(bool fill);
};
} // end namespace engine
