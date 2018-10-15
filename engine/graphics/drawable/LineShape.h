#pragma once

#include <graphics/IGraphicsElement.h>
#include <common/Vector2D.h>

namespace engine {
class LineShape : public IGraphicsElement {
    // TODO: Use Vector2d's for coordinates.
    common::Vector2D m_position1;
    common::Vector2D m_position2;

public:
    LineShape(common::Vector2D pos1, common::Vector2D pos2);

    void accept(IRenderVisitor& visitor) const override;

    common::Vector2D position1() const;
    common::Vector2D position2() const;
};
} // end namespace engine