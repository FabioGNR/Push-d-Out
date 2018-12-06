#include "World.h"
#include "Body.h"
#include "DynamicBody.h"
#include "KinematicBody.h"
#include "StaticBody.h"
#include <Box2D/Box2D.h>
#include <Box2D/Common/b2Math.h>
#include <Box2D/Dynamics/b2World.h>
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

        std::vector<Contact> m_beginContactEvents;
        std::vector<Contact> m_endContactEvents;

        void clearEvents(Body* body);

        ~WorldImpl() override = default;

        WorldImpl(const WorldImpl& other) = delete;
        WorldImpl& operator=(const WorldImpl& other) = delete;

        WorldImpl(WorldImpl&& other) = default;
        WorldImpl& operator=(WorldImpl&& other) = default;

    private:
        void BeginContact(b2Contact* contact) override
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
            const auto normal = worldManifold.normal;

            if (body1 != nullptr && body2 != nullptr) {
                Contact c{ body1->getPosition() + common::Vector2D<double>(normal.x, normal.y), body1, body2 };
                m_beginContactEvents.push_back(c);
            }
        }

        void EndContact(b2Contact* contact) override
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
            const auto normal = worldManifold.normal;

            if (body1 != nullptr && body2 != nullptr) {
                Contact c{ body1->getPosition() + common::Vector2D<double>(normal.x, normal.y), body1, body2 };
                m_endContactEvents.push_back(c);
            }
        }

    public:
        common::Vector2D<int> size;
        common::Vector2D<double> gravity;
        common::Vector2D<double> friction;

        std::unique_ptr<b2World> world;
        std::vector<Body*> bodies;

        std::vector<std::unique_ptr<ContactListener>> contactListeners;
    };

    void World::WorldImpl::clearEvents(Body* body)
    {
        m_beginContactEvents.erase(std::remove_if(m_beginContactEvents.begin(), m_beginContactEvents.end(), [&](auto& contact) {
            return contact.a == body || contact.b == body;
        }),
            m_beginContactEvents.end());

        m_endContactEvents.erase(std::remove_if(m_endContactEvents.begin(), m_endContactEvents.end(), [&](auto& contact) {
            return contact.a == body || contact.b == body;
        }),
            m_endContactEvents.end());
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
        ecs::EntityId id)
    {
        auto body = std::make_unique<DynamicBody>(position, dimension, *this);
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
        // handle contact events
        while (!m_impl->m_beginContactEvents.empty()) {
            auto& contact = m_impl->m_beginContactEvents.back();

            std::for_each(
                m_impl->contactListeners.begin(),
                m_impl->contactListeners.end(),
                [&](auto& cl) {
                    cl->beginContact(contact);
                });

            m_impl->m_beginContactEvents.pop_back();
        }

        while (!m_impl->m_endContactEvents.empty()) {
            auto& contact = m_impl->m_endContactEvents.back();

            std::for_each(
                m_impl->contactListeners.begin(),
                m_impl->contactListeners.end(),
                [&](auto& cl) {
                    cl->endContact(contact);
                });

            m_impl->m_endContactEvents.pop_back();
        }

        auto step = (deltaTime.count() / 1.0e9f);

        // convert to seconds
        m_impl->world->Step(step, m_velocityIterations, m_positionIterations);

        for (auto body : m_impl->bodies) {
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

    void World::destroyBody(Body* body, b2Body* b2Body)
    {
        m_impl->clearEvents(body);
        auto it = std::find(m_impl->bodies.begin(), m_impl->bodies.end(), body);
        m_impl->bodies.erase(it);
        m_impl->world->DestroyBody(b2Body);
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
}
}
