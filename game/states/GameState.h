#pragma once

#include "engine/ecs/World.h"
#include <game/State.h>
#include <game/systems/RenderSystem.h>
#include <memory>
#include <physics/PhysicsManager.h>
#include <physics/World.h>

namespace game {
class GameState : public engine::State {
private:
    const static int UNIT_MULTIPLIER = 2;
    const static int UNIT_SIZE = 16;

    std::unique_ptr<engine::physics::PhysicsManager> m_physicsManager;
    engine::physics::World* m_world;
    engine::ecs::World m_ecsWorld;

public:
    GameState(engine::IGame& game);
    ~GameState() override = default;

    void init() override;
    void update(std::chrono::nanoseconds timeStep) override;
    void render(engine::IRenderer& renderer) override;
};
}
