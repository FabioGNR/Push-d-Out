#pragma once

#include "common/Vector2D.h"
#include <memory>

namespace engine {
namespace physics {
    class Body {
    protected:
        std::unique_ptr<common::Vector2D> m_position;
        std::unique_ptr<common::Vector2D> m_dimensions;

        double m_angle = 0;
        int m_unitSize;
    public:
        Body(double x, double y, double width, double height, int unitSize);
        virtual ~Body() = default;

        virtual void update() = 0;

        virtual const common::Vector2D getPosition() const;
        virtual const common::Vector2D getDimensions() const;
        virtual const common::Vector2D getCenterPoint() const;

        virtual double getAngle() const;

        virtual void applyForce(const common::Vector2D &force, const common::Vector2D &point) = 0;
    };
}
}