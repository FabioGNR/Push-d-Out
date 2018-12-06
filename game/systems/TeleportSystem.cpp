#include "TeleportSystem.h"
#include <game/components/BodyComponent.h>
#include <game/components/TeleportComponent.h>

void game::systems::TeleportSystem::update(std::chrono::nanoseconds timeStep)
{
    for (auto it = m_ecsWorld->begin<components::TeleportComponent>(); it != m_ecsWorld->end<components::TeleportComponent>(); ++it) { // NOLINT
        auto& entity = m_ecsWorld->getEntity(it->first);
        auto& body = *m_ecsWorld->getComponent<components::BodyComponent>(entity).body;
        auto& tp = m_ecsWorld->getComponent<components::TeleportComponent>(entity);

        tp.timeout -= timeStep;
        if (tp.enabled && tp.timeout.count() <= 0 && tp.inRange) {
            body.setPosition(tp.position);
            tp.enabled = false;
        }
    }
}

void game::systems::TeleportSystem::render(engine::IRenderer& /* renderer */)
{
}
