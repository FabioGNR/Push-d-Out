#include "World.h"
#include <Box2D/Box2D.h>
#include "KinematicBody.h"

namespace engine {
    namespace physics {
        KinematicBody::KinematicBody(common::Vector2D<double> position, common::Vector2D<double> dimension, World& world)
                : Body(position, dimension, world)
        {
            b2BodyDef dynamicBodyDef; // set position
            dynamicBodyDef.position.Set(static_cast<float32>(position.x), static_cast<float32>(position.y));
            dynamicBodyDef.type = b2_kinematicBody;
            // create the body
            b2Body* b2Body = m_world.m_b2World->CreateBody(&dynamicBodyDef);

            b2PolygonShape groundBox; // set half-height and half-width
            groundBox.SetAsBox(static_cast<float32>(dimension.x) / 2.0f, static_cast<float32>(dimension.y) / 2.0f);
            auto fixture = b2Body->CreateFixture(&groundBox, 1.0f /* density, is not used when body is static */);
            fixture->SetFriction(static_cast<float32>(world.getFriction().x));

            // set the body
            m_body = b2Body;
        }

        KinematicBody::~KinematicBody()
        {
            m_world.m_b2World->DestroyBody(m_body);
        }

        void KinematicBody::update()
        {
            // 1 unit = 1 meter, 16 pixels are 1 unit
            m_position.x = static_cast<double>(m_body->GetPosition().x);
            m_position.y = static_cast<double>(m_body->GetPosition().y);

            m_angle = m_body->GetAngle();
        }

        void KinematicBody::applyForce(const common::Vector2D<double>& /* force */,
                                    const common::Vector2D<double>& /* point */) const
        {
            // don't apply forces.
        }

        const common::Vector2D<double> KinematicBody::getLinearVelocity() const
        {
            const auto& vel = m_body->GetLinearVelocity();
            return common::Vector2D<double>(vel.x, vel.y);
        }

        void KinematicBody::applyLinearImpulse(const common::Vector2D<double>& impulse) const
        {
            const auto impulse_f = impulse.castTo<float32>();
            m_body->ApplyLinearImpulse(b2Vec2{ impulse_f.x, impulse_f.y }, m_body->GetWorldCenter(), true);
        }

        double KinematicBody::getMass() const
        {
            return m_body->GetMass();
        }

        void KinematicBody::setLinearVelocity(common::Vector2D<double> vel) const {
            const auto velocity_f = vel.castTo<float32>();
            m_body->SetLinearVelocity(b2Vec2{ velocity_f.x, velocity_f.y });
        }
    }
}
