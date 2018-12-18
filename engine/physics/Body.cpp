#include "Body.h"
#include "World.h"
#include <Box2D/Box2D.h>
#include <memory>

namespace engine {
namespace physics {
    /**
         * Creates a new body with the size of <code>width * unitSize</code>
         * @param x     position in units of the body
         * @param y     position in units of the body
         * @param width     width in units of the body
         * @param height    height in units of the body
         * @param unitSize  size of 1 unit
         * @param world     Box2D's world object
         */
    Body::Body(common::Vector2D<double> position, common::Vector2D<double> dimension, World* world)
        : m_position{ position }
        , m_dimensions{ dimension }
        , m_world{ world }
        , m_body(nullptr)
    {
    }

    Body::~Body() = default;

    double Body::getAngle() const
    {
        return m_angle;
    }

    const common::Vector2D<double> Body::getPosition() const
    {
        // because box2d sees its position as center, shift it by half of the dimensions
        return {
            m_position.x - m_dimensions.x / 2,
            m_position.y - m_dimensions.y / 2
        };
    }

    void Body::setPosition(const common::Vector2D<double> position)
    {
        m_position = position;
    }

    const common::Vector2D<double> Body::getDimensions() const
    {
        return m_dimensions;
    }

    const common::Vector2D<double> Body::getCenterPoint() const
    {
        return common::Vector2D<double>((m_dimensions.x) / 2.0, (m_dimensions.y) / 2.0);
    }

    void Body::setEntityId(ecs::EntityId id)
    {
        m_ownerId = id;
        if (m_body != nullptr) {
            m_body->SetUserData(static_cast<void*>(&m_ownerId));
        }
    }

    ecs::EntityId Body::getEntityId() const
    {
        return *static_cast<ecs::EntityId*>(m_body->GetUserData());
    }

    void Body::setGravityScale(double scale)
    {
        m_body->SetGravityScale(static_cast<float32>(scale));
    }

    void Body::setSensor(bool isSensor)
    {
        m_body->GetFixtureList()->SetSensor(isSensor);
    }

    void Body::setBullet(bool isBullet)
    {
        m_body->SetBullet(isBullet);
    }

    double Body::getMass() const
    {
        return m_body->GetMass();
    }

    void Body::setDensity(double density)
    {
        m_body->GetFixtureList()->SetDensity(density);
    }

    std::vector<ecs::EntityId> Body::getCollidingEntities() const
    {
        std::vector<ecs::EntityId> contacts;
        auto next = m_body->GetContactList();

        while (next != nullptr) {
            auto a = *static_cast<ecs::EntityId*>(next->contact->GetFixtureA()->GetBody()->GetUserData());
            auto b = *static_cast<ecs::EntityId*>(next->contact->GetFixtureB()->GetBody()->GetUserData());
            a != getEntityId() ? contacts.push_back(a) : contacts.push_back(b);
            next = next->next;
        }

        return contacts;
    }
}
}
