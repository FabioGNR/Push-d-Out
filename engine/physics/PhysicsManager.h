#pragma once

#include <physics/World.h>
#include <vector>

class b2Body;

namespace engine {
namespace physics {
    class PhysicsManager {
    private:
        World* m_world;

    public:
        PhysicsManager();
        ~PhysicsManager();

        World* createWorld(common::Vector2D size, double gravity, double friction);
        int getUnitSize() const;
    };
}
}
