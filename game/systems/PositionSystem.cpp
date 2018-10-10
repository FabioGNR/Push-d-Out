#include "PositionSystem.h"
#include <engine/physics/Body.h>
#include <game/components/BodyComponent.h>
#include <game/components/PositionComponent.h>

namespace game {
namespace systems {
    void PositionSystem::update(std::chrono::nanoseconds /*timeStep*/)
    {
        m_world.forEachEntityWith<components::BodyComponent, components::PositionComponent>([&](engine::ecs::Entity& entity) {
            auto body = m_world.getComponent<components::BodyComponent>(entity).body;
            auto& positionComponent = m_world.getComponent<components::PositionComponent>(entity);

            positionComponent.x = body->getPosition().x;
            positionComponent.y = body->getPosition().y;
        });
    }

    void PositionSystem::render(engine::IRenderer& /*renderer*/) {}
}
}
