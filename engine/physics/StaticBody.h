#pragma once

#include "Body.h"
#include "common/Vector2D.h"
#include <memory>

class b2Body;

namespace engine {
namespace physics {
    class World;
    class StaticBody : public Body {
    private:
        b2Body* m_body;

    public:
        StaticBody(common::Vector2D<double> position, common::Vector2D<double> dimension, World& world);
        ~StaticBody() override;

        void update() override;
        void applyForce(const common::Vector2D<double>& force, const common::Vector2D<double>& point) const override;
        const common::Vector2D<double> getLinearVelocity() const override;
        void applyLinearImpulse(const common::Vector2D<double>& impulse) const override;
        double getMass() const override;
    };
}
}