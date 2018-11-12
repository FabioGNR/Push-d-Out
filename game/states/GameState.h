#pragma once

#include <engine/common/Vector2D.h>
#include <engine/ecs/World.h>
#include <engine/events/models/Subscription.h>
#include <engine/game/IGame.h>
#include <engine/game/State.h>
#include <engine/graphics/Camera.h>
#include <engine/input/InputManager.h>
#include <engine/physics/PhysicsManager.h>
#include <engine/physics/World.h>
#include <engine/sound/ISoundManager.h>

#include "game/themes/Theme.h"

#include <memory>

namespace game {
class GameState : public engine::State {
private:
    const static int UNIT_MULTIPLIER = 2;
    const static int UNIT_SIZE = 16;

    common::Vector2D<int> m_screenSize;

    std::unique_ptr<engine::sound::ISoundManager> m_soundManager;

    engine::physics::PhysicsManager m_physicsManager;
    engine::ecs::World m_ecsWorld;
    engine::input::InputManager& m_inputManager;
    std::unique_ptr<engine::physics::World> m_world;

    std::shared_ptr<
        engine::events::Subscription<engine::input::KeyMap>>
        m_inputSubscription;

public:
    GameState(
        const common::Vector2D<int>& screenSize,
        const themes::Theme& theme,
        std::unique_ptr<engine::sound::ISoundManager>
            soundManager,
        engine::input::InputManager& inputManager);

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

    void onInput(std::function<void(engine::input::KeyMap, engine::events::Subscription<engine::input::KeyMap>&)> delegate);

private:
    std::shared_ptr<engine::graphics::Camera> makeCamera(const common::Vector2D<int>& screenSize) const;
    void makeLevel();
    void makeCharacters();
};
}
