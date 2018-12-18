#include "ScoreSystem.h"
#include <game/components/LifeComponent.h>
#include <game/components/PlayerNameComponent.h>
#include <game/states/MainMenuState.h>
#include <game/states/ScoreState.h>
#include <iostream>

namespace game {
namespace systems {
    void ScoreSystem::update(std::chrono::nanoseconds /*timeStep*/)
    {
        bool playerIsAlive = false;
        std::size_t theLivingPlayers = 0;
        m_world->forEachEntityWith<components::PlayerInputComponent, components::LifeComponent>([&](engine::ecs::Entity& entity) {
            auto playerInputComponent = m_world->getComponent<components::PlayerInputComponent>(entity);
            std::string name = m_world->getComponent<components::PlayerNameComponent>(entity).name;
            auto lifeComponent = m_world->getComponent<components::LifeComponent>(entity);
            if (lifeComponent.count > 0) {
                m_score[name] += 1;
                playerIsAlive = true;
                ++theLivingPlayers;
            }
        });

        // All the players are no longer alive. Time to update the m_score and assign the winner
        if (!playerIsAlive || (m_playerCount > 1 && theLivingPlayers == 1)) {
            m_context->next(std::make_unique<ScoreState>(*m_context, m_score));
        }
    }
    void ScoreSystem::render(engine::IRenderer& /*renderer*/)
    {
        // Do nothing
    }
}
}
