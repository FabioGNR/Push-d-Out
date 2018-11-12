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

#include <utility>

namespace game {
GameState::GameState(
    const common::Vector2D<int>& screenSize,
    const themes::Theme& theme,
    std::unique_ptr<engine::sound::ISoundManager> soundManager,
    engine::input::InputManager& inputManager)
    : m_screenSize(screenSize)
    , m_soundManager(std::move(soundManager))
    , m_inputManager(inputManager)
    , m_world(m_physicsManager.createWorld(
          common::Vector2D<int>(40, 24),
          theme.getGravity(),
          theme.getFriction()))
{
}

void GameState::init()
{
    // Read Level based on JSON file
    makeLevel();
    // Build characters into the ECS and physics world
    makeCharacters();

    auto camera = makeCamera(m_screenSize);
    // Add render system
    m_ecsWorld.addSystem<systems::RenderSystem>(engine::definitions::SystemPriority::Medium, m_ecsWorld, camera);

    engine::sound::Music music("assets/sounds/bgm.wav");
    m_soundManager->play(music);
}

void GameState::update(std::chrono::nanoseconds timeStep)
{
    m_world->update(timeStep);
    m_ecsWorld.update(timeStep);
}

void GameState::render(engine::IRenderer& renderer)
{
    m_ecsWorld.render(renderer);
}

void GameState::resume()
{
    if (m_inputSubscription != nullptr) {
        m_inputSubscription->open();
    }
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

std::shared_ptr<engine::graphics::Camera> GameState::makeCamera(const common::Vector2D<int>& screenSize) const
{
    return std::make_shared<engine::graphics::Camera>(UNIT_MULTIPLIER * UNIT_SIZE, screenSize);
}

void GameState::makeCharacters()
{
    builders::CharacterBuilder builder{ m_ecsWorld, *m_world, m_inputManager };
    builder.build();
}
void GameState::makeLevel()
{
    const auto level = level::LevelReader::getLevel(level::LevelReader::readJSON("assets/levels/base-level.json"));
    level::LevelReader::createEntities(m_ecsWorld, *m_world, level);
}
void GameState::onInput(std::function<void(engine::input::KeyMap,
        engine::events::Subscription<engine::input::KeyMap>&)>
        delegate)
{
    m_inputSubscription = m_inputManager.subscribe(std::move(delegate));
}
} // end namespace game
