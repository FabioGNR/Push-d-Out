#pragma once

#include "common/Vector2D.h"
#include <memory>

namespace engine {
namespace physics {
    class World;
    class Body {
    protected:
        common::Vector2D<double> m_position;
        common::Vector2D<double> m_dimensions;

        double m_angle = 0;
        int m_unitSize;

        World& m_world;

    public:
        Body(common::Vector2D<double> position, common::Vector2D<double> dimension, World& world);
        virtual ~Body() = default;

        virtual void update() = 0;

        virtual const common::Vector2D<double> getPosition() const;
        virtual const common::Vector2D<double> getDimensions() const;
        virtual const common::Vector2D<double> getCenterPoint() const;

        virtual double getAngle() const;

        virtual void applyForce(const common::Vector2D<double>& force, const common::Vector2D<double>& point) = 0;
    };
}
}