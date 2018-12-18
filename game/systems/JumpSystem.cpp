#include "JumpSystem.h"

#include <algorithm>
#include <engine/common/RNG.h>
#include <engine/ecs/Entity.h>
#include <engine/exceptions/EntityNotFoundException.h>
#include <engine/sound/SoundEffect.h>
#include <game/components/BodyComponent.h>
#include <game/components/JumpComponent.h>
#include <game/components/MoveComponent.h>
#include <game/components/PositionComponent.h>
#include <game/components/TileComponent.h>
#include <sstream>

namespace game {
namespace systems {
    void JumpSystem::update(std::chrono::nanoseconds /* timeStep */)
    {
        m_world.forEachEntityWith<components::JumpComponent, components::BodyComponent>([&](engine::ecs::Entity& entity) {
            auto& jump = m_world.getComponent<components::JumpComponent>(entity);

            if (mayJump(entity)) {
                auto& body = *m_world.getComponent<components::BodyComponent>(entity).body;
                auto impulse = common::Vector2D<double>(0, body.getMass() * jump.delta.y);
                body.applyLinearImpulse(impulse);

                if (jump.delta.y > 0) {
                    std::stringstream soundPath{};
                    soundPath << "assets/sounds/jump-";
                    soundPath << std::to_string(common::RNG::generate(0, 1));
                    soundPath << ".wav";
                    const engine::sound::SoundEffect sound(soundPath.str(), 0);
                    m_soundManager->play(sound);
                }
            }

            jump.delta = { 0, 0 }; // reset jump height
        });
    }

    bool JumpSystem::mayJump(engine::ecs::Entity& entity)
    {
        auto& body = *m_world.getComponent<components::BodyComponent>(entity).body;
        auto& position = m_world.getComponent<components::PositionComponent>(entity).position;
        auto collisions = body.getCollidingEntities();

        if (collisions.empty()) {
            return false;
        }

        for (auto& collision : collisions) {
            try {
                auto& collisionEntity = m_world.getEntity(collision);
                auto& collisionPosition = m_world.getComponent<components::PositionComponent>(collisionEntity).position;
                if (position.y > collisionPosition.y && collisionEntity.hasComponent<components::TileComponent>()) {
                    return true;
                }
            } catch (engine::exceptions::EntityNotFoundException&) {
                // don't reset jump when colliding with bullets
            }
        }

        return false;
    }

    void JumpSystem::render(engine::IRenderer& /* renderer */) {}
}
}
