#include "PhysicsManager.h"
#include <Box2D/Box2D.h>
#include <iostream>
#include <physics/World.h>

namespace engine {
namespace physics {
    PhysicsManager::PhysicsManager()
        : m_world{ nullptr }
    {
    }

    /**
     * @param size in units
     * @param gravity
     * @param friction
     * @return pointer to World object
     */
    World* PhysicsManager::createWorld(common::Vector2D<int> size, double gravity, double friction)
    {
        auto world = new World(size, gravity, friction);

        delete m_world; // delete last world
        m_world = world;
        return world;
    }

    PhysicsManager::~PhysicsManager()
    {
        delete m_world;
    }
}
}
