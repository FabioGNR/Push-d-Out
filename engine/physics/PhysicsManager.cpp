#include "PhysicsManager.h"
#include <Box2D/Box2D.h>
#include <iostream>

void PhysicsManager::doPhysics()
{
    std::cout << "Hello, world" << std::endl;
    b2Vec2 gravity(0.0f, -9.81f);
    b2World world{ gravity };
    std::cout << gravity.y << std::endl;
}
