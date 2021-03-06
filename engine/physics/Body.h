#pragma once

#include "engine/common/Vector2D.h"
#include <memory>

namespace engine {
namespace physics {
    class World;

    class Body {
    protected:
        common::Vector2D<double> m_position;
        common::Vector2D<double> m_dimensions;

        double m_angle = 0;

        World& m_world;

    public:
        Body(common::Vector2D<double> position, common::Vector2D<double> dimension, World& world);

        Body(const Body& other) = delete;
        Body& operator=(const Body& other) = delete;

        Body(Body&& other) = delete;
        Body& operator=(Body&& other) = delete;
        virtual ~Body();

        virtual void update() = 0;

        virtual const common::Vector2D<double> getPosition() const;
        virtual const common::Vector2D<double> getDimensions() const;
        virtual const common::Vector2D<double> getCenterPoint() const;

        virtual double getAngle() const;

        virtual void applyForce(const common::Vector2D<double>& force, const common::Vector2D<double>& point) const = 0;

        virtual const common::Vector2D<double> getLinearVelocity() const = 0;
        virtual void setLinearVelocity(common::Vector2D<double> vel) const = 0;
        virtual void applyLinearImpulse(const common::Vector2D<double>& impulse) const = 0;
        virtual double getMass() const = 0;
    };
}
}
