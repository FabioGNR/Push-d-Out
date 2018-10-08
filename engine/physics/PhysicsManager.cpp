#include "PhysicsManager.h"
#include <Box2D/Box2D.h>
#include <iostream>
#include <physics/World.h>

namespace engine {
namespace physics {
    PhysicsManager::PhysicsManager(int unitSize)
    {
        m_worlds = std::vector<World*>();
        m_unitSize = unitSize;
    }

    /**
     * @param size in units
     * @param gravity
     * @param friction
     * @return pointer to World object
     */
    World* PhysicsManager::createWorld(common::Vector2D size, double gravity, double friction)
    {
        size.x *= m_unitSize;
        size.y *= m_unitSize;

        auto world = new World(size, gravity, friction, m_unitSize);
        m_worlds.push_back(world);
        return world;
    }

    PhysicsManager::~PhysicsManager()
    {
        for (World* world : m_worlds) {
            delete world;
        }
    }

    int PhysicsManager::getUnitSize() const
    {
        return m_unitSize;
    }
}
}