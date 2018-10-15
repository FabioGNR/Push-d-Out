#include "DynamicBody.h"
#include "World.h"
#include <Box2D/Box2D.h>

namespace engine {
namespace physics {
    DynamicBody::DynamicBody(common::Vector2D<double> position, common::Vector2D<double> dimension, World& world)
        : Body(position, dimension, world)
    {
        b2BodyDef bodyDef;
        // You must set the body type to b2_dynamicBody if you want the body to move in response to forces
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set((float32)position.x, (float32)position.y);
        bodyDef.fixedRotation = true;

        // create new body from world object
        b2Body* b2Body = m_world.m_b2World->CreateBody(&bodyDef);
        b2PolygonShape dynamicBox; // set height and width
        dynamicBox.SetAsBox((float32)dimension.x / 2.0f, (float32)dimension.y / 2.0f);

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &dynamicBox;
        fixtureDef.density = 1.0f;

        auto friction = m_world.getFriction();
        fixtureDef.friction = (float32)friction.x;

        b2Body->CreateFixture(&fixtureDef);

        // set the body
        m_body = b2Body;
    }

    DynamicBody::~DynamicBody()
    {
        m_world.m_b2World->DestroyBody(m_body);
    }

    void DynamicBody::update()
    {
        // 1 unit = 1 meter, 16 pixels are 1 unit
        m_position.x = m_body->GetPosition().x;
        m_position.y = m_body->GetPosition().y;

        m_angle = m_body->GetAngle();
    }

    void DynamicBody::applyForce(const common::Vector2D<double>& force, const common::Vector2D<double>& point)
    {
        b2Vec2 b2Force((float32)force.x, (float32)force.y);
        b2Vec2 b2Point((float32)point.x, (float32)point.y);
        m_body->ApplyForce(b2Force, b2Point, true);
    }
}
}
