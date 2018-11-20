#include <Box2D/Box2D.h>
#include <Box2D/Common/b2Math.h>
#include <Box2D/Dynamics/b2World.h>

#include <chrono>
#include <memory>

#include "Body.h"
#include "DynamicBody.h"
#include "KinematicBody.h"
#include "StaticBody.h"
#include "World.h"

namespace engine {
namespace physics {
    class World::WorldImpl {
    public:
        WorldImpl(const common::Vector2D<int>& size,
            const common::Vector2D<double>& gravity,
            const common::Vector2D<double>& friction)
            : size(size)
            , gravity(gravity)
            , friction(friction)
            , world(nullptr)
        {
        }

        WorldImpl(const WorldImpl& other) = delete;
        WorldImpl& operator=(const WorldImpl& other) = delete;

        WorldImpl(WorldImpl&& other) = default;
        WorldImpl& operator=(WorldImpl&& other) = default;

        virtual ~WorldImpl() = default;

        common::Vector2D<int> size;
        common::Vector2D<double> gravity;
        common::Vector2D<double> friction;

        std::unique_ptr<b2World> world;

        std::vector<std::unique_ptr<Body>> bodies;
    };

    World::World(common::Vector2D<int> size, double gravity, double friction)
        : m_impl(std::make_unique<WorldImpl>(
              size,
              common::Vector2D<double>{ 0.0, gravity },
              common::Vector2D<double>{ friction, 0.0 }))
    {
        const b2Vec2 grav{ 0, (float32)gravity };
        m_impl->world = std::make_unique<b2World>(grav);
    }

    World::~World()
    {
        m_impl->bodies.clear();
    }

    common::Vector2D<double> World::getGravity() const
    {
        const b2Vec2 grav = m_impl->world->GetGravity();
        return common::Vector2D<double>(static_cast<double>(grav.x), static_cast<double>(grav.y));
    }

    const common::Vector2D<double>& World::getFriction() const
    {
        return m_impl->friction;
    }

    /**
         * Creates and adds a body to the world object which is static
         * @param x position
         * @param y position
         * @param height  height
         * @param width   width
         */
    Body* World::createStaticBody(common::Vector2D<double> position, common::Vector2D<double> dimension)
    {
        m_impl->bodies.push_back(
            std::make_unique<StaticBody>(position, dimension, *this));
        return m_impl->bodies.back().get();
    }

    /**
         * Creates and adds a body to the world object which responds to forces
         * @param x position
         * @param y position
         * @param height  height
         * @param width   width
         */
    Body* World::createDynamicBody(common::Vector2D<double> position, common::Vector2D<double> dimension)
    {
        m_impl->bodies.push_back(
            std::make_unique<DynamicBody>(position, dimension, *this));
        return m_impl->bodies.back().get();
    }

    Body* World::createKinematicBody(common::Vector2D<double> position, common::Vector2D<double> dimension)
    {
        m_impl->bodies.push_back(
            std::make_unique<KinematicBody>(position, dimension, *this));
        return m_impl->bodies.back().get();
    }

    const std::vector<std::unique_ptr<Body>>& World::getBodies() const
    {
        return m_impl->bodies;
    }

    void World::update(std::chrono::nanoseconds deltaTime)
    {
        auto step = (deltaTime.count() / 1.0e9f) * m_updateScale;

        // convert to seconds
        m_impl->world->Step(step, m_velocityIterations, m_positionIterations);

        for (auto& body : m_impl->bodies) {
            body->update();
        }
    }

    const common::Vector2D<int>& World::getSize() const
    {
        return m_impl->size;
    }

    b2Body* World::createBody(const b2BodyDef& def) const
    {
        return m_impl->world->CreateBody(&def);
    }

    void World::destroyBody(b2Body* body)
    {
        m_impl->world->DestroyBody(body);
    }

    void World::setGravity(common::Vector2D<double> gravity)
    {
        auto convertedGravity = gravity.castTo<float32>();
        const b2Vec2 b2Gravity{ convertedGravity.x, convertedGravity.y };
        m_impl->world->SetGravity(b2Gravity);
    }

    void World::setUpdateScale(double scale)
    {
        m_updateScale = scale;
    }

    void World::resetUpdateScale()
    {
        m_updateScale = 1;
    }

    double World::updateScale()
    {
        return m_updateScale;
    }
}
}
