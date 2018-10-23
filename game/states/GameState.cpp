#include "GameState.h"
#include "game/builders/CharacterBuilder.h"
#include "game/level/levelReader/LevelReader.h"
#include "game/systems/CameraSystem.h"
#include "game/systems/RenderSystem.h"
#include "game/systems/PlayerInputSystem.h"
#include <engine/physics/Body.h>
#include <game/Game.h>
#include <game/components/DimensionComponent.h>
#include <game/components/PositionComponent.h>
#include <game/components/SpriteComponent.h>
#include <game/themes/Earth.h>
#include <graphics/Color.h>
#include <graphics/drawable/RectangleShape.h>
#include <sound/SDL/SDLSoundManager.h>
#include <sound/Sound.h>

#include <iostream>
#include <random>

namespace game {
GameState::GameState(engine::IGame& game)
    : engine::State(game)
    , m_soundManager(new engine::sound::SDLSoundManager)
{
    m_physicsManager = std::make_unique<engine::physics::PhysicsManager>();
    themes::Theme theme = themes::Earth {};
    m_world = m_physicsManager->createWorld(common::Vector2D<int>(40, 24), theme.getGravity(), theme.getFriction());
}

void GameState::init()
{
    engine::sound::Music music("assets/sounds/bgm.wav");
    m_soundManager->play(music);

    Game& game = dynamic_cast<Game&>(m_context);

    // Read level based on JSON file
    auto level = game::levelReader::getLevel(game::levelReader::readJSON("assets/levels/base-level.json"));
    game::levelReader::createEntities(m_ecsWorld, *m_world, level);

    // Build characters into the ECS and physics world
    game::builders::CharacterBuilder builder { m_ecsWorld, *m_world, game.getInputManager() };
    builder.build();

    // Set-up camera
    auto camera = std::make_shared<engine::graphics::Camera>(UNIT_MULTIPLIER * UNIT_SIZE, game.getScreenSize());
    m_ecsWorld.addSystem<systems::CameraSystem>(engine::definitions::SystemPriority::Medium, camera);

    // Add render system
    m_ecsWorld.addSystem<systems::RenderSystem>(engine::definitions::SystemPriority::Medium, m_ecsWorld, camera);
}

void GameState::update(std::chrono::nanoseconds timeStep)
{
    static int volume = 100;
    static std::chrono::nanoseconds timeElapsed(0);
    timeElapsed += timeStep;
    m_world->update(timeStep);

    if (timeElapsed > std::chrono::seconds(2)) {
        timeElapsed = std::chrono::nanoseconds::zero();
        m_soundManager->setMusicVolume(volume + 10);
        m_soundManager->setSfxVolume(volume);

        //volume -= 20;
    }

    m_ecsWorld.update(timeStep);
}

void GameState::render(engine::IRenderer& renderer)
{
    m_ecsWorld.render(renderer);
}
}
