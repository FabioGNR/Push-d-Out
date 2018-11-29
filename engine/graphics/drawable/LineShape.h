#pragma once

#include <common/Vector2D.h>
#include <graphics/Color.h>
#include <graphics/IGraphicsElement.h>

namespace engine {
class LineShape : public IGraphicsElement {
    common::Vector2D<int> m_position1;
    common::Vector2D<int> m_position2;
    const Color& m_color;

public:
    LineShape(common::Vector2D<int> pos1, common::Vector2D<int> pos2, const Color& color);

    ~LineShape() override = default;

    void accept(IRenderVisitor& visitor) const override;

    const common::Vector2D<int>& position1() const;
    const common::Vector2D<int>& position2() const;
    const Color& color() const;
};
} // end namespace engine