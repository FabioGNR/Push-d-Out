#pragma once

#include <engine/ecs/System.h>
#include <engine/ecs/World.h>
#include <engine/game/IGame.h>
#include <game/components/PlayerInputComponent.h>

namespace game {
namespace systems {
    class ScoreSystem : public engine::ecs::BaseSystem<ScoreSystem> {
        engine::ecs::World* m_world;
        engine::IGame* m_context;
        std::map<int, long int> m_score{};
        int m_playerCount{};

    public:
        ScoreSystem(engine::ecs::World* world, engine::IGame* context, int playerCount)
            : m_world{ world }
            , m_context{ context }
            , m_playerCount{ playerCount }
        {
            if (m_playerCount < 4) {
                ++m_playerCount;
            }
        }
        void update(std::chrono::nanoseconds timeStep) override;
        void render(engine::IRenderer& renderer) override;
    };
}
}
