#include "DynamicBody.h"
#include "World.h"
#include <Box2D/Box2D.h>

namespace engine {
namespace physics {
    DynamicBody::DynamicBody(common::Vector2D<double> position, common::Vector2D<double> dimension, World& world, int groupIndex)
        : Body(position, dimension, &world)
    {
        b2BodyDef bodyDef;
        // You must set the body type to b2_dynamicBody if you want the body to move in response to forces
        bodyDef.type = b2_dynamicBody;
        position += dimension / 2; // adjust for centered origin in box2d
        bodyDef.position.Set(static_cast<float32>(position.x), static_cast<float32>(position.y));
        bodyDef.fixedRotation = true;

        // create new body from world object
        b2Body* b2Body = m_world->createBody(bodyDef);
        b2PolygonShape dynamicBox; // set half height and half width
        dynamicBox.SetAsBox((float32)dimension.x / 2.0f, (float32)dimension.y / 2.0f);
        b2FixtureDef fixtureDef;
        fixtureDef.shape = &dynamicBox;
        fixtureDef.density = 1.0f;
        fixtureDef.filter.groupIndex = static_cast<int16>(groupIndex);

        auto friction = m_world->getFriction();
        fixtureDef.friction = (float32)friction.x;

        b2Body->CreateFixture(&fixtureDef);

        // set the body
        m_body = b2Body;
    }

    DynamicBody::~DynamicBody()
    {
        m_world->destroyBody(this, m_body);
    }

    void DynamicBody::update()
    {
        // 1 unit = 1 meter, 16 pixels are 1 unit
        m_position.x = m_body->GetPosition().x;
        m_position.y = m_body->GetPosition().y;

        m_angle = m_body->GetAngle();
    }

    void DynamicBody::setPosition(common::Vector2D<double> d)
    {
        Body::setPosition(d);
        m_body->SetTransform(b2Vec2{ static_cast<float32>(d.x), static_cast<float32>(d.y) }, m_body->GetAngle());
    }

    void DynamicBody::applyForce(const common::Vector2D<double>& force, const common::Vector2D<double>& point) const
    {
        b2Vec2 b2Force((float32)force.x, (float32)force.y);
        b2Vec2 b2Point((float32)point.x, (float32)point.y);
        m_body->ApplyForce(b2Force, b2Point, true);
    }

    const common::Vector2D<double> DynamicBody::getLinearVelocity() const
    {
        b2Vec2 vel = m_body->GetLinearVelocity();
        return common::Vector2D<double>(vel.x, vel.y);
    }

    void DynamicBody::applyLinearImpulse(const common::Vector2D<double>& impulse) const
    {
        auto impulsef = impulse.castTo<float32>();
        m_body->ApplyLinearImpulse(b2Vec2{ impulsef.x, impulsef.y }, m_body->GetWorldCenter(), true);
    }

    void DynamicBody::setLinearVelocity(common::Vector2D<double> vel) const
    {
        auto velf = vel.castTo<float32>();
        m_body->SetLinearVelocity(b2Vec2{ velf.x, velf.y });
    }
}
}
