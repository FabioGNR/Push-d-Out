//
// Created by Matthias Aarnoutse on 19/09/2018.
//

#include <iostream>
#include <Box2D/Box2D.h>
#include "PhysicsManager.h"

void PhysicsManager::doPhysics() {
    std::cout << "Hello, world";
    b2Vec2 gravity(0.0f, -9.81f);
    b2World world {gravity};
    std::cout << gravity.y;
}