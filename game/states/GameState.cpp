#include "GameState.h"

#include <engine/game/IGame.h>
#include <engine/graphics/Camera.h>
#include <engine/physics/PhysicsManager.h>
#include <engine/sound/SDL/SDLSoundManager.h>

#include <game/Game.h>
#include <game/builders/CharacterBuilder.h>
#include <game/level/reader/LevelReader.h>
#include <game/systems/CameraSystem.h>
#include <game/systems/RenderSystem.h>
#include <game/themes/Earth.h>
#include <game/themes/Theme.h>

namespace game {
GameState::GameState(engine::IGame& game)
    : engine::State(game)
    , m_soundManager(new engine::sound::SDLSoundManager)
    , m_inputManager(dynamic_cast<Game&>(game).getInputManager())
{
    m_physicsManager = std::make_unique<engine::physics::PhysicsManager>();
    themes::Theme theme = themes::Earth{};
    m_world = m_physicsManager->createWorld(common::Vector2D<int>(40, 24), theme.getGravity(), theme.getFriction());
}

void GameState::init()
{
    engine::sound::Music music("assets/sounds/bgm.wav");
    m_soundManager->play(music);

    auto& game = dynamic_cast<Game&>(m_context);

    // Read Level based on JSON file
    auto level = level::LevelReader::getLevel(level::LevelReader::readJSON("assets/levels/base-level.json"));
    level::LevelReader::createEntities(m_ecsWorld, *m_world, level);

    // Build characters into the ECS and physics world
    game::builders::CharacterBuilder builder{ m_ecsWorld, *m_world, game.getInputManager() };
    builder.build();

    // Set-up camera
    auto camera = std::make_shared<engine::graphics::Camera>(UNIT_MULTIPLIER * UNIT_SIZE, game.getScreenSize());
    m_ecsWorld.addSystem<systems::CameraSystem>(engine::definitions::SystemPriority::Medium, camera);

    // Add render system
    m_ecsWorld.addSystem<systems::RenderSystem>(engine::definitions::SystemPriority::Medium, m_ecsWorld, camera);

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
}

void GameState::subscribeInput()
{
    m_inputSubscription = m_inputManager.subscribe([&](engine::input::KeyMap keyMap, auto&) {
        if (keyMap.hasKeyState(engine::input::Keys::ESCAPE, engine::input::KeyStates::PRESSED)) {
            m_context.previous();
        }
    });
}
}
