#include "MovementSystem.h"

#include <algorithm>
#include <engine/ecs/Entity.h>
#include <game/components/BodyComponent.h>
#include <game/components/LevelMetaComponent.h>
#include <game/components/MoveComponent.h>
#include <game/components/PositionComponent.h>

namespace game {
namespace systems {
    void MovementSystem::update(std::chrono::nanoseconds /* timeStep */)
    {
        std::vector<engine::ecs::Entity*> moveComponentsToRemove;

        auto levelIt = m_world.begin<components::LevelMetaComponent>();
        components::LevelMetaComponent* level = nullptr;
        if (levelIt != m_world.end<components::LevelMetaComponent>()) {
            level = dynamic_cast<components::LevelMetaComponent*>(levelIt->second.get());
        }

        m_world.forEachEntityWith<components::MoveComponent, components::BodyComponent, components::PositionComponent>([&](engine::ecs::Entity& entity) {
            auto& delta = m_world.getComponent<components::MoveComponent>(entity).delta;
            auto& body = *m_world.getComponent<components::BodyComponent>(entity).body;
            auto& position = m_world.getComponent<components::PositionComponent>(entity);

            auto velocity = body.getLinearVelocity();

            double deltaX = 0;
            if (delta.x < 0) {
                deltaX = std::min(velocity.x - 0.1, delta.x);
            } else if (delta.x > 0) {
                deltaX = std::max(velocity.x + 0.1, delta.x);
            } else {
                deltaX = velocity.x * 0.98;
            }

            auto impulse = common::Vector2D<double>(body.getMass() * (deltaX - velocity.x), body.getMass() * delta.y);
            if (level->theme.glide) {
                body.applyForce(impulse, position.position);
            } else {
                body.applyLinearImpulse(impulse);
            }

            moveComponentsToRemove.push_back(&entity);
        });
        for (auto* entity : moveComponentsToRemove) {
            m_world.removeComponent<components::MoveComponent>(*entity);
        }
    }

    void MovementSystem::render(engine::IRenderer& /* renderer */) {}
}
}
