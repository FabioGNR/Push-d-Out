#pragma once

#include "engine/common/Vector2D.h"
#include "engine/graphics/Color.h"
#include "engine/graphics/IGraphicsElement.h"

namespace engine {
class Circle : public IGraphicsElement {
    common::Vector2D<double> m_center;
    double m_radius;
    bool m_fill;
    Color m_color;

public:
    Circle(common::Vector2D<double> center, double radius, const Color& color, bool fill = false);
    virtual ~Circle() = default;

    void accept(IRenderVisitor& visitor) const override;

    double radius() const;
    const common::Vector2D<double> center() const;
    const Color& color() const;
    bool fill() const;

    void radius(double radius);
    void center(common::Vector2D<double> center);
    void fill(bool fill);
};
} // end namespace engine
