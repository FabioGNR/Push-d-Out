#pragma once

#include "engine/common/Vector2D.h"
#include "engine/physics/Body.h"
namespace engine {
namespace physics {
    struct CollisionObject {
        int entityID;
        common::Vector2D<double> velocity;
        CollisionObject(int entity, common::Vector2D<double> velocity);
    };

    class Collision {
    public:
        CollisionObject A;
        CollisionObject B;
    };
}
}
