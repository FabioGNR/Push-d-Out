#pragma once

#include <physics/World.h>
#include <vector>

class b2Body;

namespace engine {
namespace physics {
    class PhysicsManager {
    private:
        std::vector<World*> m_worlds;
        int m_unitSize;

    public:
        explicit PhysicsManager(int unitSize);

        ~PhysicsManager();

        World* createWorld(double gravity, double friction);

        int getUnitSize() const;
    };
}
}
