#include "StaticBody.h"
#include "World.h"
#include <Box2D/Box2D.h>

namespace engine {
namespace physics {
    StaticBody::StaticBody(common::Vector2D<double> position, common::Vector2D<double> dimension, World& world)
        : Body(position, dimension, world)
    {
        b2BodyDef groundBodyDef; // set position
        groundBodyDef.position.Set(static_cast<float32>(position.x), static_cast<float32>(position.y));

        // create the body
        b2Body* b2Body = m_world.m_b2World->CreateBody(&groundBodyDef);

        b2PolygonShape groundBox; // set half-height and half-width
        groundBox.SetAsBox(static_cast<float32>(dimension.x) / 2.0f, static_cast<float32>(dimension.y) /* TODO: /2.0f */);
        b2Body->CreateFixture(&groundBox, 1.0f /* density, is not used when body is static */);

        // set the body
        m_body = b2Body;
    }

    StaticBody::~StaticBody()
    {
        m_world.m_b2World->DestroyBody(m_body);
    }

    void StaticBody::update()
    {
        // 1 unit = 1 meter, 16 pixels are 1 unit
        m_position.x = static_cast<double>(m_body->GetPosition().x);
        m_position.y = static_cast<double>(m_body->GetPosition().y);

        m_angle = m_body->GetAngle();
    }

    void StaticBody::applyForce(const common::Vector2D<double>& /* force */,
        const common::Vector2D<double>& /* point */)
    {
        // don't apply forces.
    }
}
}
