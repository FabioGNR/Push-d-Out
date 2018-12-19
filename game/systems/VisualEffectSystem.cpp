#include "VisualEffectSystem.h"
#include "game/components/VisualEffectComponent.h"
#include <game/components/DestructibleComponent.h>
#include <game/components/SpriteComponent.h>

namespace game {
namespace systems {

    void VisualEffectSystem::update(std::chrono::nanoseconds /*timeStep*/)
    {
        m_ecsWorld->forEachEntityWith<components::VisualEffectComponent, components::SpriteComponent>([&](engine::ecs::Entity& entity) {
            auto spriteComponent = m_ecsWorld->getComponent<components::SpriteComponent>(entity);
            auto visualEffectComponent = m_ecsWorld->getComponent<components::VisualEffectComponent>(entity);
            if (spriteComponent.completed) {
                m_ecsWorld->addComponent<components::DestructibleComponent>(entity);
            }
        });
    }

    void VisualEffectSystem::render(engine::IRenderer& /*renderer*/)
    {
    }
}
}