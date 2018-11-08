#include "Collision.h"

namespace engine {
namespace physics {
    CollisionObject::CollisionObject(int entity, common::Vector2D<double> velocity)
        : entityID(entity)
        , velocity(velocity)
    {
    }
}
}