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

    World* PhysicsManager::createWorld(double gravity, double friction)
    {
        auto world = new World{ gravity, friction, m_unitSize };
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