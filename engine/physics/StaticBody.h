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
        StaticBody(common::Vector2D position, common::Vector2D dimension, World& world);

        void update() override;

        ~StaticBody() override;

        void applyForce(const common::Vector2D& force, const common::Vector2D& point) override;
    };
}
}