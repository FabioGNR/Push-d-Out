#include "MovementSystem.h"

#include <algorithm>
#include <engine/ecs/Entity.h>
#include <engine/exceptions/EntityNotFoundException.h>
#include <game/components/BodyComponent.h>
#include <game/components/LevelMetaComponent.h>
#include <game/components/MoveComponent.h>
#include <game/components/PlayerInputComponent.h>
#include <game/components/PositionComponent.h>
#include <game/level/Tiles.h>

namespace game {
namespace systems {
    void MovementSystem::update(std::chrono::nanoseconds /* timeStep */)
    {
        std::vector<engine::ecs::Entity*> moveComponentsToRemove;
        auto levelIt = m_world.begin<components::LevelMetaComponent>();
        engine::ecs::Entity* level = nullptr;
        if (levelIt != m_world.end<components::LevelMetaComponent>()) {
            level = &m_world.getEntity(levelIt->first);
        }

        m_world.forEachEntityWith<components::MoveComponent, components::BodyComponent, components::PositionComponent>([&](engine::ecs::Entity& entity) {
            auto& theme = m_world.getComponent<components::LevelMetaComponent>(*level).theme;
            auto& move = m_world.getComponent<components::MoveComponent>(entity);
            auto& body = *m_world.getComponent<components::BodyComponent>(entity).body;
            auto velocity = body.getLinearVelocity();

            double multiplier = 1;
            body.setGravityScale(1.0);
            if (entity.hasComponent<components::PlayerInputComponent>()) {
                // restrain movement when there is no ground underneath the body
                if (shouldRestrainMovement(entity)) {
                    multiplier = theme.airSpeedModifier;
                    body.setGravityScale(4.0);
                }
            }

            double scalar = 20;
            if (move.useImpulse || !theme.slide) {
                scalar = 0.1;
            }

            double deltaX = 0;
            if (move.delta.x < 0) {
                deltaX = std::min(velocity.x - scalar, move.delta.x);
            } else if (move.delta.x > 0) {
                deltaX = std::max(velocity.x + scalar, move.delta.x);
            } else {
                deltaX = velocity.x * 0.98;
            }

            auto impulse = common::Vector2D<double>(body.getMass() * (deltaX - velocity.x) * multiplier, body.getMass() * move.delta.y);
            if (move.useImpulse || !theme.slide) {
                body.applyLinearImpulse(impulse);
            } else {
                body.applyForce(impulse, body.getCenterPoint());
            }

            move.delta = common::Vector2D<double>(0, 0);
        });
    }

    void MovementSystem::render(engine::IRenderer& /* renderer */) {}

    bool MovementSystem::shouldRestrainMovement(engine::ecs::Entity& entity)
    {
        auto& body = *m_world.getComponent<components::BodyComponent>(entity).body;
        auto& position = m_world.getComponent<components::PositionComponent>(entity).position;
        auto collisions = body.getCollidingEntities();

        if (collisions.empty()) {
            return true;
        }

        for (auto& collision : collisions) {
            try {
                auto& collisionEntity = m_world.getEntity(collision);
                auto& collisionPosition = m_world.getComponent<components::PositionComponent>(collisionEntity).position;

                if (position.y > collisionPosition.y) {
                    return false;
                }
            } catch (engine::exceptions::EntityNotFoundException&) {
            }
        }

        return true;
    }
}
}
