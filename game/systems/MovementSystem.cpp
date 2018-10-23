#include "MovementSystem.h"
#include <algorithm>
#include <ecs/Entity.h>
#include <game/components/BodyComponent.h>
#include <game/components/MoveComponent.h>
#include <game/components/PositionComponent.h>

namespace game {
namespace systems {
    void MovementSystem::update(std::chrono::nanoseconds /* timeStep */)
    {
        m_world.forEachEntityWith<components::MoveComponent, components::BodyComponent>([&](engine::ecs::Entity& entity) {
            auto& delta = m_world.getComponent<components::MoveComponent>(entity).delta;
            auto& body = m_world.getComponent<components::BodyComponent>(entity).body;

            auto velocity = body->getLinearVelocity();
            
            double deltaX = 0;
            if (delta.x < 0) {
                deltaX = std::min(velocity.x - 0.1, delta.x);
            } else if (delta.x > 0) {
                deltaX = std::max(velocity.x + 0.1, delta.x);
            } else {
                deltaX = velocity.x * 0.98;
            }

            auto impulse = common::Vector2D<double>(body->getMass() * (deltaX - velocity.x), body->getMass() * delta.y);
            body->applyLinearImpulse(impulse);

            m_world.removeComponent<components::MoveComponent>(entity);
        });
    }

    void MovementSystem::render(engine::IRenderer& /* renderer */) {}
}
}
