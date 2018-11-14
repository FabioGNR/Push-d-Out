#include "GameState.h"
#include "PauseMenuState.h"

#include <engine/game/IGame.h>
#include <engine/graphics/Camera.h>
#include <engine/physics/PhysicsManager.h>
#include <engine/sound/SDL/SDLSoundManager.h>

#include <game/Game.h>
#include <game/builders/CharacterBuilder.h>
#include <game/level/Theme.h>
#include <game/level/reader/LevelReader.h>
#include <game/systems/CameraSystem.h>
#include <game/systems/RenderSystem.h>
#include <game/systems/items/ReverseGravitySystem.h>

namespace game {
GameState::GameState(engine::IGame& game)
    : engine::State(game)
    , m_soundManager(new engine::sound::SDLSoundManager)
    , m_inputManager(dynamic_cast<Game&>(game).getInputManager())
{
    m_physicsManager = std::make_unique<engine::physics::PhysicsManager>();
}

void GameState::init()
{
    auto& game = dynamic_cast<Game&>(m_context);

    // Read Level based on JSON file
    level::LevelReader lr{};
    auto level = lr.build(lr.parse("assets/levels/base-level.json"));

    // Create level from theme
    m_world = m_physicsManager->createWorld(common::Vector2D<int>(level.width, level.height), level.theme.gravity, level.theme.friction);
    level::LevelReader::createEntities(m_ecsWorld, *m_world, level);

    // Play track
    engine::sound::Music music("assets/sounds/" + level.theme.trackName);
    m_soundManager->play(music);

    // Build characters into the ECS and physics world
    game::builders::CharacterBuilder builder{ m_ecsWorld, *m_world, game.getInputManager(), 4 };
    builder.build();

    // Set-up camera
    auto camera = std::make_shared<engine::graphics::Camera>(UNIT_MULTIPLIER * UNIT_SIZE, game.getScreenSize());
    m_ecsWorld.addSystem<systems::CameraSystem>(engine::definitions::SystemPriority::Medium, m_ecsWorld, camera);

    // Add render system
    m_ecsWorld.addSystem<systems::RenderSystem>(engine::definitions::SystemPriority::Medium, m_ecsWorld, camera);

    m_ecsWorld.addSystem<systems::items::ReverseGravitySystem>(engine::definitions::SystemPriority::Low, m_ecsWorld, *m_world);

    subscribeInput();
}

void GameState::update(std::chrono::nanoseconds timeStep)
{
    static int volume = 100;
    static std::chrono::nanoseconds timeElapsed(0);
    timeElapsed += timeStep;
    m_world->update(timeStep);

    if (timeElapsed > std::chrono::seconds(2)) {
        timeElapsed = std::chrono::nanoseconds::zero();
        m_soundManager->setMusicVolume(engine::sound::Volume{ volume + 10 });
        m_soundManager->setSfxVolume(engine::sound::Volume{ volume });

        //volume -= 20;
    }

    m_ecsWorld.update(timeStep);
}

void GameState::render(engine::IRenderer& renderer)
{
    m_ecsWorld.render(renderer);
}

void GameState::resume()
{
    subscribeInput();
}

void GameState::pause()
{
    m_inputSubscription->close();
    m_inputSubscription = nullptr;
}

void GameState::close()
{
    if (m_inputSubscription != nullptr) {
        m_inputSubscription->close();
    }
    m_soundManager->pause();
}

void GameState::subscribeInput()
{
    m_inputSubscription = m_inputManager.subscribe([&](engine::input::KeyMap keyMap, auto&) {
        //TODO: add check for 'start' button on controller(s) when controller input is supported
        if (keyMap.hasKeyState(engine::input::Keys::ESCAPE, engine::input::KeyStates::PRESSED)) {
            auto pauseMenu = std::make_unique<PauseMenuState>(m_context);
            m_context.next(std::move(pauseMenu));
        }
    });
}
}
