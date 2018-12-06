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
    ~Circle() override = default;

    void draw(const IRenderer& renderer) const override;

    void accept(const IRenderVisitor& visitor) const override;

    const common::Vector2D<int>& position() const override;
    void setPosition(const common::Vector2D<int>& position) override;

    const Color& color() const;

    double radius() const;
    void radius(double radius);

    bool fill() const;
    void fill(bool fill);
};
} // end namespace engine
