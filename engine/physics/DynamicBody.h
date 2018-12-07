#pragma once

#include "Body.h"

#include <engine/common/Vector2D.h>

#include <memory>

class b2Body;

namespace engine {
namespace physics {
    class World;
    class DynamicBody : public Body {
    public:
        DynamicBody(common::Vector2D<double> position, common::Vector2D<double> dimension, World& world);
        DynamicBody(const DynamicBody& other) = delete;
        DynamicBody& operator=(const DynamicBody& other) = delete;

        DynamicBody(DynamicBody&& other) = delete;
        DynamicBody& operator=(DynamicBody&& other) = delete;
        ~DynamicBody() override;

        void update() override;
        void applyForce(const common::Vector2D<double>& force, const common::Vector2D<double>& point) const override;
        const common::Vector2D<double> getLinearVelocity() const override;
        void setPosition(common::Vector2D<double> d) override;
        void setLinearVelocity(common::Vector2D<double> vel) const override;
        void applyLinearImpulse(const common::Vector2D<double>& impulse) const override;
    };
}
}