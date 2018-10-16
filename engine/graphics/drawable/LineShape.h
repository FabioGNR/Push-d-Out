#pragma once

#include <graphics/IGraphicsElement.h>
#include <common/Vector2D.h>

namespace engine {
class LineShape : public IGraphicsElement {
    common::Vector2D<int> m_position1;
    common::Vector2D<int> m_position2;

public:
    LineShape(common::Vector2D<int> pos1, common::Vector2D<int> pos2);

    void accept(IRenderVisitor& visitor) const override;

    common::Vector2D<int> position1() const;
    common::Vector2D<int> position2() const;
};
} // end namespace engine