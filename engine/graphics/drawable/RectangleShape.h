#pragma once

#include <graphics/Color.h>
#include <graphics/IGraphicsElement.h>

namespace engine {
class RectangleShape : public IGraphicsElement {
    // TODO: Use Vector2d's for size.
    int m_width;
    int m_height;
    // TODO: Use Vector2d's for coordinates.
    int m_x;
    int m_y;

    Color m_color;

public:
    RectangleShape(int x, int y, int width, int height, const Color& color);

    void accept(IRenderVisitor& visitor) const override;

    int width() const;
    int height() const;
    int x() const;
    int y() const;
    const Color& color() const;

    void setWidth(int width);
    void setHeight(int height);
    void setX(int x);
    void setY(int y);
};
} // end namespace engine
