#pragma once

#include "Body.h"
#include "common/Vector2D.h"
#include <memory>

class b2Body;

namespace engine {
namespace physics {
    class World;
    class DynamicBody : public Body {
    private:
        b2Body* m_body;

    public:
        DynamicBody(common::Vector2D<double> position, common::Vector2D<double>, World& world);

        ~DynamicBody() override;

        void update() override;

        void applyForce(const common::Vector2D<double>& force, const common::Vector2D<double>& point) override;
    };
}
}