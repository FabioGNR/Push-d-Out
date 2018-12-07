#pragma once

#include "Body.h"
#include "common/Vector2D.h"
#include <memory>

class b2Body;

namespace engine {
namespace physics {
    class World;
    class KinematicBody : public Body {
    public:
        KinematicBody(common::Vector2D<double> position, common::Vector2D<double> dimension, World& world);
        KinematicBody(const KinematicBody& other) = delete;
        KinematicBody& operator=(const KinematicBody& other) = delete;

        KinematicBody(KinematicBody&& other) = delete;
        KinematicBody& operator=(KinematicBody&& other) = delete;
        ~KinematicBody() override;

        void update() override;
        void applyForce(const common::Vector2D<double>& force, const common::Vector2D<double>& point) const override;
        const common::Vector2D<double> getLinearVelocity() const override;
        void setLinearVelocity(common::Vector2D<double> vel) const override;
        void applyLinearImpulse(const common::Vector2D<double>& impulse) const override;
    };
}
}