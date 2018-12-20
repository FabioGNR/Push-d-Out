#include "CooldownSystem.h"
#include <engine/physics/Body.h>
#include <game/components/BodyComponent.h>
#include <game/components/PortalComponent.h>
#include <game/components/PositionComponent.h>

namespace game {
namespace systems {
    void CooldownSystem::update(std::chrono::nanoseconds timeStep)
    {
        m_world.forEachEntityWith<components::PortalComponent>([&](engine::ecs::Entity& entity) {
            auto& portal = m_world.getComponent<components::PortalComponent>(entity);
            portal.timeout -= timeStep;
        });
    }

    void CooldownSystem::render(engine::IRenderer& /*renderer*/)
    {
    }
}
}
