#include "StaticBody.h"
#include "World.h"
#include <Box2D/Box2D.h>

namespace engine {
namespace physics {
    StaticBody::StaticBody(double x, double y, double width, double height, int unitSize,
        World& world)
        : Body(x, y, width, height, unitSize)
        , m_world{ world }
    {
        b2BodyDef groundBodyDef; // set position
        groundBodyDef.position.Set((float32)x, (float32)y);

        // create the body
        b2Body* b2Body = m_world.m_b2World->CreateBody(&groundBodyDef);

        b2PolygonShape groundBox; // set height and width
        groundBox.SetAsBox(((float32)width / 2.0f), ((float32)height / 2.0f));
        b2Body->CreateFixture(&groundBox, 0.0f /* density, is not used when body is static */);

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
        m_position->x = m_body->GetPosition().x * m_unitSize;
        m_position->y = m_body->GetPosition().y * m_unitSize;

        m_angle = m_body->GetAngle();
    }

    void StaticBody::applyForce(const common::Vector2D& /* force */,
        const common::Vector2D& /* point */)
    {
        // don't apply forces.
    }
}
}
