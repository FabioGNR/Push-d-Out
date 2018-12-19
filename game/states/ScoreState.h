#pragma once

#include <engine/common/Vector2D.h>
#include <engine/ecs/World.h>
#include <engine/events/models/Subscription.h>
#include <engine/game/State.h>
#include <engine/graphics/Camera.h>
#include <engine/input/InputManager.h>
#include <engine/physics/PhysicsManager.h>
#include <engine/physics/World.h>
#include <engine/sound/ISoundManager.h>

#include <game/Game.h>

#include <chrono>
#include <utility>

namespace game {
class ScoreState : public engine::State {
private:
    std::map<std::string, long double> m_score{};
    std::chrono::nanoseconds m_nsTillNextState{ std::chrono::seconds{ 10 } };

    const static int UNIT_MULTIPLIER = 2;
    const static int UNIT_SIZE = 16;

    std::unique_ptr<engine::physics::PhysicsManager> m_physicsManager;
    std::unique_ptr<engine::physics::World> m_world;
    engine::graphics::Camera m_camera;
    engine::ecs::World m_ecsWorld;

    engine::sound::ISoundManager* m_soundManager{};

    engine::input::InputManager* m_inputManager;
    std::shared_ptr<engine::events::Subscription<engine::input::maps::InputMap>> m_inputSubscription;

public:
    ScoreState(engine::IGame& context, std::map<std::string, long double> score)
        : engine::State{ context }
        , m_score{ std::move(score) }
        , m_physicsManager(std::make_unique<engine::physics::PhysicsManager>())
        , m_inputManager(dynamic_cast<Game&>(context).getInputManager())
    {
    }

    void update(std::chrono::nanoseconds timeStep) override;
    void render(engine::IRenderer& renderer) override;
    void init() override;
    void resume() override;
    void pause() override;
    void close() override;

private:
    void initPlayers();
    void addExplosion(const common::Vector2D<double>& pos);
};
}
