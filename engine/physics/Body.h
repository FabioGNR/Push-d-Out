#pragma once

#include "common/Vector2D.h"
#include <memory>

namespace engine {
namespace physics {
    class World;
    class Body {
    protected:
        common::Vector2D m_position;
        common::Vector2D m_dimensions;

        double m_angle = 0;
        int m_unitSize;

        World& m_world;
    public:
        Body(double x, double y, double width, double height, int unitSize, World& world);
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