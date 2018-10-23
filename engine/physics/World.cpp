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
#include "KinematicBody.h"

namespace engine {
namespace physics {

    World::World(common::Vector2D<int> size, double gravity, double friction) : m_size{size}
    {
        b2Vec2 grav{ 0, (float32)gravity };

        m_gravity = std::make_unique<common::Vector2D<double>>(0.0, gravity);
        m_friction = std::make_unique<common::Vector2D<double>>(friction, 0.0);
        m_b2World = new b2World(grav);
        m_bodies = std::vector<Body*>{};
    }

    World::~World()
    {
        delete m_b2World;
    }

    const common::Vector2D<double> World::getGravity() const
    {
        return *m_gravity;
    }

    const common::Vector2D<double> World::getFriction() const
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
    const Body* World::createStaticBody(common::Vector2D<double> position, common::Vector2D<double> dimension)
    {
        auto body = new StaticBody(position, dimension, *this);
        m_bodies.push_back(body); // save body
        return body;
    }

    /**
         * Creates and adds a body to the world object which responds to forces
         * @param x position
         * @param y position
         * @param height  height
         * @param width   width
         */
    const Body* World::createDynamicBody(common::Vector2D<double> position, common::Vector2D<double> dimension)
    {
        auto body = new DynamicBody(position, dimension, *this);
        m_bodies.push_back(body); // save body
        return body;
    }

    const Body* World::createKinematicBody(common::Vector2D<double> position, common::Vector2D<double> dimension)
    {
        auto body = new KinematicBody(position, dimension, *this);
        m_bodies.push_back(body); // save body
        return body;
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

    const common::Vector2D<int> World::getSize() const {
        return m_size;
    }
}
}
