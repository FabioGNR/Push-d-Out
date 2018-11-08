#include "PhysicsManager.h"
#include <Box2D/Box2D.h>
#include <iostream>
#include <physics/World.h>

namespace engine {
namespace physics {
    PhysicsManager::PhysicsManager() = default;
    PhysicsManager::~PhysicsManager() = default;

    /**
     * @param size in units
     * @param gravity
     * @param friction
     * @return pointer to World object
     */
    std::unique_ptr<World> PhysicsManager::createWorld(common::Vector2D<int> size, double gravity, double friction)
    {
        return std::make_unique<World>(size, gravity, friction);
    }
}
}
