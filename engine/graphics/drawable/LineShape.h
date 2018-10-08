#pragma once

#include <graphics/IGraphicsElement.h>

namespace engine {
class LineShape : public IGraphicsElement {
    // TODO: Use Vector2d's for coordinates.
    int m_x1;
    int m_x2;
    int m_y1;
    int m_y2;

public:
    LineShape(int x1, int x2, int y1, int y2);

    void accept(IRenderVisitor& visitor) const override;

    int x1() const;
    int x2() const;
    int y1() const;
    int y2() const;
};
} // end namespace engine