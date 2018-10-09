#include <Box2D/Box2D.h>
#include <Box2D/Common/b2Math.h>
#include <Box2D/Dynamics/b2World.h>
#include <memory>
#include <chrono>
#include <iostream>

#include "Body.h"
#include "DynamicBody.h"
#include "StaticBody.h"
#include "World.h"

namespace engine {
namespace physics {

    World::World(common::Vector2D size, double gravity, double friction, int unitSize) : m_size{size}, m_unitSize{unitSize}
    {
        b2Vec2 grav{ 0, (float32)gravity };

        m_gravity = std::make_unique<common::Vector2D>(0.0, gravity);
        m_friction = std::make_unique<common::Vector2D>(friction, 0.0);
        m_b2World = new b2World(grav);
        m_bodies = std::vector<Body*>{};
    }

    World::~World()
    {
        delete m_b2World;
    }

    const common::Vector2D World::getGravity() const
    {
        return *m_gravity;
    }

    const common::Vector2D World::getFriction() const
    {
        return *m_friction;
    }

    /**
         * Creates and adds a body to the world object which is static
         * @param x position
         * @param y position
         * @param height  height
         * @param width   width
         */
    void World::createStaticBody(int x, int y, int width, int height)
    {
        auto body = new StaticBody(x, y, width, height, m_unitSize, *this);
        m_bodies.push_back(body); // save body
    }

    /**
         * Creates and adds a body to the world object which responds to forces
         * @param x position
         * @param y position
         * @param height  height
         * @param width   width
         */
    void World::createDynamicBody(int x, int y, int width, int height)
    {
        auto body = new DynamicBody(x, y, width, height, m_unitSize, *this);
        m_bodies.push_back(body); // save body
    }

    const std::vector<Body*> World::getBodies() const
    {
        return m_bodies;
    }

    void World::update(std::chrono::nanoseconds deltaTime)
    {
        // convert to seconds
        m_b2World->Step(deltaTime.count() / 1.0e9f, m_velocityIterations, m_positionIterations);

        for (auto body : m_bodies) {
            body->update();
        }
    }

    const common::Vector2D World::getSize() const {
        return m_size;
    }
}
}
