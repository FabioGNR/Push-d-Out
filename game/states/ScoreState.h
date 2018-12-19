#pragma once

#include <engine/ecs/World.h>
#include <engine/game/State.h>
#include <engine/graphics/Camera.h>
#include <engine/physics/PhysicsManager.h>
#include <engine/ui/UISystem.h>

#include <game/Game.h>
#include <game/hud/HUD.h>

#include <chrono>
#include <utility>

namespace game {
class ScoreState : public engine::State {
private:
    std::unique_ptr<engine::physics::PhysicsManager> m_physicsManager;
    std::unique_ptr<engine::physics::World> m_world;
    engine::graphics::Camera m_camera;
    std::unique_ptr<game::hud::HUD> m_hud;
    engine::ecs::World m_ecsWorld;

    engine::sound::ISoundManager* m_soundManager{};

    engine::input::InputManager* m_inputManager;
    std::shared_ptr<engine::events::Subscription<engine::input::maps::InputMap>> m_inputSubscription;

    std::map<int, long double> m_score{};

    std::chrono::nanoseconds m_remainingTimeTillNextState = std::chrono::seconds{ 10 };

public:
    ScoreState(engine::IGame& context, std::map<int, long double> score)
        : engine::State{ context }
        , m_inputManager(dynamic_cast<Game&>(context).getInputManager())
        , m_score{ std::move(score) }
    {
        m_physicsManager = std::make_unique<engine::physics::PhysicsManager>();
    }

    void update(std::chrono::nanoseconds timeStep) override;
    void render(engine::IRenderer& renderer) override;
    void init() override;
    void resume() override;
    void pause() override;
    void close() override;

private:
    void addExplosion(const common::Vector2D<double>& pos);
    void initPlayers();
};
}
