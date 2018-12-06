#include "JumpSystem.h"

#include <engine/ecs/Entity.h>
#include <game/components/BodyComponent.h>
#include <game/components/MoveComponent.h>
#include <game/components/PositionComponent.h>

#include <algorithm>
#include <game/components/JumpComponent.h>
#include <iostream>

namespace game {
namespace systems {
    void JumpSystem::update(std::chrono::nanoseconds /* timeStep */)
    {
        m_world.forEachEntityWith<components::JumpComponent, components::BodyComponent>([&](engine::ecs::Entity& entity) {
            auto& jump = m_world.getComponent<components::JumpComponent>(entity);
            auto& body = *m_world.getComponent<components::BodyComponent>(entity).body;

            auto impulse = common::Vector2D<double>(0, body.getMass() * jump.delta.y);
            body.applyLinearImpulse(impulse);

            jump.delta = { 0, 0 }; // reset jump height
        });
    }

    void JumpSystem::render(engine::IRenderer& /* renderer */) {}
}
}
