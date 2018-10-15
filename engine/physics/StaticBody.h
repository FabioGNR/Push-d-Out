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

        void update() override;

        ~StaticBody() override;

        void applyForce(const common::Vector2D<double>& force, const common::Vector2D<double>& point) override;
    };
}
}