#include "World.h"
#include "Body.h"
#include "ContactImpl.h"
#include "DynamicBody.h"
#include "KinematicBody.h"
#include "StaticBody.h"
#include <Box2D/Box2D.h>
#include <Box2D/Common/b2Math.h>
#include <Box2D/Dynamics/b2World.h>
#include <Box2D/Dynamics/b2WorldCallbacks.h>
#include <chrono>
#include <memory>
#include <vector>

namespace engine {
namespace physics {

    class World::WorldImpl : b2ContactListener {
    public:
        WorldImpl(
            const common::Vector2D<int>& size,
            const common::Vector2D<double>& gravity,
            const common::Vector2D<double>& friction)
            : size(size)
            , gravity(gravity)
            , friction(friction)
            , world(nullptr)
        {
        }

        void raycast(const common::Vector2D<double>& start, const common::Vector2D<double>& end, const RaycastCallback& callback);

        ~WorldImpl() override = default;

        WorldImpl(const WorldImpl& other) = delete;
        WorldImpl& operator=(const WorldImpl& other) = delete;

        WorldImpl(WorldImpl&& other) = default;
        WorldImpl& operator=(WorldImpl&& other) = default;

    private:
        class Box2DRaycastCallback;

        std::unique_ptr<ContactImpl> mapContact(b2Contact* contact)
        {
            Body* body1 = nullptr;
            Body* body2 = nullptr;

            for (auto& body : bodies) {
                if (contact->GetFixtureA()->GetBody() == body->m_body) {
                    body1 = body;
                }

                if (contact->GetFixtureB()->GetBody() == body->m_body) {
                    body2 = body;
                }
            }

            b2WorldManifold worldManifold;
            contact->GetWorldManifold(&worldManifold);
            auto size = static_cast<size_t>(contact->GetManifold()->pointCount);
            auto normal = common::Vector2D<double>(worldManifold.normal.x, worldManifold.normal.y);

            std::vector<common::Vector2D<double>> points{};
            points.reserve(size);

            for (size_t i = 0; i < size; ++i) {
                points.emplace_back(worldManifold.points[i].x, worldManifold.points[i].y);
            }

            if (body1 != nullptr && body2 != nullptr) {
                auto c = std::make_unique<ContactImpl>(contact);
                c->points = points;
                c->a = body1;
                c->b = body2;
                c->normal = normal;
                return c;
            }
            return nullptr;
        }

        void BeginContact(b2Contact* contact) override
        {
            auto c = mapContact(contact);
            if (c != nullptr) {
                std::for_each(contactListeners.begin(), contactListeners.end(), [&](auto& cl) {
                    cl->beginContact(*c);
                });
            }
        }

        void EndContact(b2Contact* contact) override
        {
            auto c = mapContact(contact);
            if (c != nullptr) {
                std::for_each(contactListeners.begin(), contactListeners.end(), [&](auto& cl) {
                    cl->endContact(*c);
                });
            }
        }

        void PreSolve(b2Contact* contact, const b2Manifold* /* oldManifold */) override
        {
            auto c = mapContact(contact);
            if (c != nullptr) {
                std::for_each(contactListeners.begin(), contactListeners.end(), [&](auto& cl) {
                    cl->preSolve(*c);
                });
            }
        }

        void PostSolve(b2Contact* contact, const b2ContactImpulse* /* impulse */) override
        {
            auto c = mapContact(contact);
            if (c != nullptr) {
                std::for_each(contactListeners.begin(), contactListeners.end(), [&](auto& cl) {
                    cl->postSolve(*c);
                });
            }
        }

        Body* findBody(b2Body* body);

    public:
        common::Vector2D<int> size;
        common::Vector2D<double> gravity;
        common::Vector2D<double> friction;

        std::unique_ptr<b2World> world;
        std::vector<Body*> bodies;
        std::vector<b2Body*> bodiesToDestroy;

        std::vector<std::unique_ptr<ContactListener>> contactListeners;
    };

    class World::WorldImpl::Box2DRaycastCallback : public b2RayCastCallback {
        RaycastCallback m_callback;
        WorldImpl* m_worldImpl;

    public:
        Box2DRaycastCallback(WorldImpl* worldImpl, RaycastCallback callback)
            : m_callback{ std::move(callback) }
            , m_worldImpl{ worldImpl }
        {
        }

        float32 ReportFixture(b2Fixture* fixture, const b2Vec2& b2Point, const b2Vec2& b2Normal, float32 fraction) override
        {
            auto* b2Body = fixture->GetBody();
            auto* body = m_worldImpl->findBody(b2Body);
            if (body != nullptr) {
                RaycastHit hit{};
                hit.body = body;
                hit.point = { b2Point.x, b2Point.y };
                hit.normal = { b2Normal.x, b2Normal.y };
                hit.fraction = fraction;
                double returnedFraction = m_callback(hit);
                return static_cast<float32>(returnedFraction);
            }
            return -1; // no callback was called so just skip this one
        }
    };

    void World::WorldImpl::raycast(const common::Vector2D<double>& start, const common::Vector2D<double>& end,
        const RaycastCallback& callback)
    {

        Box2DRaycastCallback b2Callback{ this, callback };

        b2Vec2 b2Start{ static_cast<float32>(start.x), static_cast<float32>(start.y) };
        b2Vec2 b2End{ static_cast<float32>(end.x), static_cast<float32>(end.y) };
        world->RayCast(&b2Callback, b2Start, b2End);
    }

    Body* World::WorldImpl::findBody(b2Body* body)
    {
        auto bodyIt = std::find_if(bodies.begin(), bodies.end(), [&](Body* vectorBody) {
            return vectorBody->m_body == body;
        });
        if (bodyIt != bodies.end()) {
            return *bodyIt;
        }
        return nullptr;
    }

    // this piece doesn't format for some reason, so whatever
    // clang-format off
    World::World(common::Vector2D<int> size, double gravity, double friction)
        : m_impl(std::make_unique<WorldImpl>(
            size,
            common::Vector2D<double>{ 0.0, gravity },
            common::Vector2D<double>{ friction, 0.0 }))
    {
        const b2Vec2 grav{ 0, (float32)gravity };
        m_impl->world = std::make_unique<b2World>(grav);
        m_impl->world->SetContactListener((b2ContactListener*)m_impl.get());
    }
    // clang-format on

    World::~World()
    {
        m_impl->world->SetContactListener(nullptr);
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
    std::unique_ptr<Body> World::createStaticBody(common::Vector2D<double> position, common::Vector2D<double> dimension, ecs::EntityId id)
    {
        auto body = std::make_unique<StaticBody>(position, dimension, *this);
        body->setEntityId(id);

        m_impl->bodies.push_back(body.get());
        return std::move(body);
    }

    /**
     * Creates and adds a body to the world object which responds to forces
     * @param x position
     * @param y position
     * @param height  height
     * @param width   width
     */
    std::unique_ptr<Body> World::createDynamicBody(common::Vector2D<double> position,
        common::Vector2D<double> dimension,
        ecs::EntityId id,
        int groupIndex)
    {
        auto body = std::make_unique<DynamicBody>(position, dimension, *this, groupIndex);
        body->setEntityId(id);

        m_impl->bodies.push_back(body.get());
        return std::move(body);
    }

    std::unique_ptr<Body> World::createKinematicBody(common::Vector2D<double> position,
        common::Vector2D<double> dimension,
        ecs::EntityId id)
    {
        auto body = std::make_unique<StaticBody>(position, dimension, *this);
        body->setEntityId(id);

        m_impl->bodies.push_back(body.get());
        return std::move(body);
    }

    void World::update(std::chrono::nanoseconds deltaTime)
    {
        for (auto* body : m_impl->bodiesToDestroy) {
            m_impl->world->DestroyBody(body);
        }
        m_impl->bodiesToDestroy.clear();

        auto step = (deltaTime.count() / 1.0e9f);

        // convert to seconds
        m_impl->world->Step(step, m_velocityIterations, m_positionIterations);

        for (auto body : m_impl->bodies) {
            body->update();
        }

        for (auto& cl : m_impl->contactListeners) {
            cl->update(deltaTime);
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

    void World::destroyBody(Body* body, b2Body* b2Body)
    {
        auto it = std::find(m_impl->bodies.begin(), m_impl->bodies.end(), body);
        m_impl->bodies.erase(it);

        m_impl->bodiesToDestroy.push_back(b2Body);
    }

    void World::setGravity(common::Vector2D<double> gravity)
    {
        auto convertedGravity = gravity.castTo<float32>();
        const b2Vec2 b2Gravity{ convertedGravity.x, convertedGravity.y };
        m_impl->world->SetGravity(b2Gravity);
    }

    void World::addContactListener(std::unique_ptr<ContactListener> contactListener)
    {
        m_impl->contactListeners.push_back(std::move(contactListener));
    }

    void World::raycast(const common::Vector2D<double>& start, const common::Vector2D<double>& end,
        const RaycastCallback& callback)
    {
        m_impl->raycast(start, end, callback);
    }
}
}
