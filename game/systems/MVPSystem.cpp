#include "MVPSystem.h"
#include <game/components/DimensionComponent.h>
#include <game/components/PlayerInputComponent.h>
#include <game/components/PlayerNameComponent.h>
#include <game/components/PositionComponent.h>
#include <game/states/GameState.h>

namespace game {
namespace systems {
    void MVPSystem::update(std::chrono::nanoseconds /*timeStep*/)
    {
        auto& crownEntity = m_world->getEntity(m_entityId);
        auto& crownPosition = m_world->getComponent<components::PositionComponent>(crownEntity).position;
        auto& crownDimension = m_world->getComponent<components::DimensionComponent>(crownEntity).dimension;

        m_world->forEachEntityWith<components::PlayerInputComponent>([&](auto& entity) {
            const auto& playerInputComponent = m_world->getComponent<components::PlayerInputComponent>(entity);
            if (playerInputComponent.controllerId == GameState::MVP) {
                auto positionComponent = m_world->getComponent<components::PositionComponent>(entity).position;
                auto dimensionComponent = m_world->getComponent<components::DimensionComponent>(entity).dimension;

                auto centerPositionX = positionComponent.x + dimensionComponent.x / 2 - crownDimension.x / 2;
                crownPosition = { centerPositionX, positionComponent.y + dimensionComponent.y + 0.1 };
            }
        });
    }
    void MVPSystem::render(engine::IRenderer& /* renderer */)
    {
    }
}
}
