#pragma once

#include <engine/ecs/World.h>
#include <engine/game/State.h>
#include <engine/input/InputManager.h>
#include <engine/physics/PhysicsManager.h>
#include <engine/physics/World.h>
#include <engine/sound/ISoundManager.h>

#include <engine/events/models/Subscription.h>
#include <memory>

namespace game {
class GameState : public engine::State {
private:
    const static int UNIT_MULTIPLIER = 2;
    const static int UNIT_SIZE = 16;

    std::unique_ptr<engine::physics::PhysicsManager> m_physicsManager;
    std::unique_ptr<engine::physics::World> m_world;
    engine::ecs::World m_ecsWorld;

    std::unique_ptr<engine::sound::ISoundManager> m_soundManager;

    engine::input::InputManager& m_inputManager;
    std::shared_ptr<engine::events::Subscription<engine::input::KeyMap>> m_inputSubscription;

public:
    explicit GameState(engine::IGame& game);
    ~GameState() override = default;

    GameState(const GameState& other) = delete;
    GameState& operator=(const GameState& other) = delete;

    GameState(GameState&& other) = delete;
    GameState& operator=(GameState&& other) = delete;

    void init() override;
    void update(std::chrono::nanoseconds timeStep) override;
    void render(engine::IRenderer& renderer) override;

    void resume() override;

    void pause() override;

    void close() override;

    void subscribeInput();
};
}
