#include "GameState.h"
#include "PauseMenuState.h"
#include <engine/game/IGame.h>
#include <engine/graphics/Camera.h>
#include <engine/physics/PhysicsManager.h>
#include <engine/sound/SDL/SDLSoundManager.h>
#include <game/Game.h>
#include <game/builders/BunnyBuilder.h>
#include <game/builders/CharacterBuilder.h>
#include <game/builders/SpriteBuilder.h>
#include <game/components/DimensionComponent.h>
#include <game/components/PlayerNameComponent.h>
#include <game/components/PositionComponent.h>
#include <game/components/SpriteComponent.h>
#include <game/config/ConfigurationRepository.h>
#include <game/level/Theme.h>
#include <game/level/reader/LevelReader.h>
#include <game/systems/AISystem.h>
#include <game/systems/AnimationSystem.h>
#include <game/systems/BackgroundSystem.h>
#include <game/systems/CameraSystem.h>
#include <game/systems/CheatsSystem.h>
#include <game/systems/CooldownSystem.h>
#include <game/systems/GarbageCollectorSystem.h>
#include <game/systems/InventorySystem.h>
#include <game/systems/ItemSystem.h>
#include <game/systems/JumpSystem.h>
#include <game/systems/LifeSystem.h>
#include <game/systems/MVPSystem.h>
#include <game/systems/MovementSystem.h>
#include <game/systems/NpcSpawnSystem.h>
#include <game/systems/OutOfBoundsCleanUpSystem.h>
#include <game/systems/PlayerInputSystem.h>
#include <game/systems/PlayerNameSystem.h>
#include <game/systems/PositionSystem.h>
#include <game/systems/PunchingSystem.h>
#include <game/systems/ScoreSystem.h>
#include <game/systems/TeleportSystem.h>
#include <game/systems/VisualEffectSystem.h>
#include <game/systems/WeaponSystem.h>
#include <game/systems/items/ReverseGravitySystem.h>
#include <utility>

namespace game {

std::string GameState::MVP = "";

GameState::GameState(std::string levelToPlay, engine::IGame& game)
    : engine::State(game)
    , m_inputManager(dynamic_cast<Game&>(game).getInputManager())
    , m_levelToPlay(std::move(levelToPlay))
{
    m_physicsManager = std::make_unique<engine::physics::PhysicsManager>();
}

void GameState::init()
{
    auto& game = dynamic_cast<Game&>(m_context);

    m_soundManager = game.getSoundManager();

    // Read Level based on JSON file
    level::LevelReader lr{};
    auto level = lr.build(lr.parse(m_levelToPlay));

    // Create level from theme
    m_world = m_physicsManager->createWorld(common::Vector2D<int>(level.width, level.height), level.theme.gravity, level.theme.friction);
    level::LevelReader::createEntities(m_ecsWorld, *m_world, level);

    // Play track
    engine::sound::Music music("assets/sounds/" + level.theme.trackName);
    m_soundManager->play(music);

    // Add various systems
    m_ecsWorld.addSystem<systems::PlayerInputSystem>(engine::definitions::SystemPriority::Medium, m_ecsWorld, m_inputManager);
    m_ecsWorld.addSystem<systems::JumpSystem>(engine::definitions::SystemPriority::Medium, m_ecsWorld, m_soundManager);
    m_ecsWorld.addSystem<systems::PositionSystem>(engine::definitions::SystemPriority::Medium, m_ecsWorld);
    m_ecsWorld.addSystem<systems::WeaponSystem>(engine::definitions::SystemPriority::Medium, &m_ecsWorld, m_world.get(), m_inputManager, &m_camera);
    m_ecsWorld.addSystem<systems::ItemSystem>(engine::definitions::SystemPriority::Medium, m_ecsWorld, *m_world, m_inputManager);
    m_ecsWorld.addSystem<systems::InventorySystem>(engine::definitions::SystemPriority::Medium, m_ecsWorld, m_inputManager);
    m_ecsWorld.addSystem<systems::items::ReverseGravitySystem>(engine::definitions::SystemPriority::Medium, m_ecsWorld, *m_world, m_soundManager);
    m_ecsWorld.addSystem<systems::TeleportSystem>(engine::definitions::SystemPriority::Medium, &m_ecsWorld);
    m_ecsWorld.addSystem<systems::NpcSpawnSystem>(engine::definitions::SystemPriority::Medium, &m_ecsWorld, m_world.get());
    m_ecsWorld.addSystem<systems::PunchingSystem>(engine::definitions::SystemPriority::Medium, &m_ecsWorld, m_world.get(), m_inputManager, m_soundManager);
    m_ecsWorld.addSystem<systems::LifeSystem>(engine::definitions::SystemPriority::Low, &m_ecsWorld, &m_camera);
    m_ecsWorld.addSystem<systems::AnimationSystem>(engine::definitions::SystemPriority::Medium, &m_ecsWorld, &m_camera);
    m_ecsWorld.addSystem<systems::VisualEffectSystem>(engine::definitions::SystemPriority::Medium, &m_ecsWorld);
    m_ecsWorld.addSystem<systems::CooldownSystem>(engine::definitions::SystemPriority::Low, m_ecsWorld);
    m_ecsWorld.addSystem<systems::MovementSystem>(engine::definitions::SystemPriority::Low, m_ecsWorld);
    m_ecsWorld.addSystem<systems::AISystem>(engine::definitions::SystemPriority::Low, &m_ecsWorld);
    m_ecsWorld.addSystem<systems::CheatsSystem>(engine::definitions::SystemPriority::Low, &m_ecsWorld, m_inputManager);
    m_ecsWorld.addSystem<systems::OutOfBoundsCleanUpSystem>(engine::definitions::SystemPriority::Low, &m_ecsWorld, &m_camera);
    m_ecsWorld.addSystem<systems::GarbageCollectorSystem>(engine::definitions::SystemPriority::High, &m_ecsWorld);
    m_ecsWorld.addSystem<systems::ScoreSystem>(engine::definitions::SystemPriority::Low, &m_ecsWorld, &m_context, m_inputManager->getConnectedControllers().size());

    // Set-up camera
    m_camera = engine::graphics::Camera(UNIT_MULTIPLIER * UNIT_SIZE, game.getScreenSize());
    m_camera.setPosition({ level.width / 2.0, level.height / 2.0 });
    m_ecsWorld.addSystem<systems::CameraSystem>(engine::definitions::SystemPriority::Medium, &m_ecsWorld, &m_camera);
    m_ecsWorld.addSystem<systems::BackgroundSystem>(engine::definitions::SystemPriority::High, m_ecsWorld, game.getScreenSize());

    // Add some nice contact listeners
    m_world->addContactListener(std::make_unique<listeners::PlatformContactListener>(m_ecsWorld, m_inputManager->getMap()));

    // Build characters into the ECS and physics world
    game::builders::CharacterBuilder builder{ m_ecsWorld, *m_world, m_inputManager };
    builder.build();

    m_ecsWorld.addSystem<systems::PlayerNameSystem>(engine::definitions::SystemPriority::Medium, &m_ecsWorld, &m_camera);

    // Create HUD
    m_hud = std::make_unique<game::hud::HUD>(game.window(), m_ecsWorld, &m_camera, m_inputManager);

    std::map<std::string, components::SpriteComponent> map = builders::SpriteBuilder{ "assets/sprites/misc/misc.png", "assets/sprites/misc/misc.json" }.build();
    m_ecsWorld.forEachEntityWith<components::PlayerInputComponent>([&](auto& entity) {
        std::string name = m_ecsWorld.getComponent<components::PlayerNameComponent>(entity).name;
        auto playerInputComponent = m_ecsWorld.getComponent<components::PlayerInputComponent>(entity);
        auto position = m_ecsWorld.getComponent<components::PositionComponent>(entity).position;

        if (name == GameState::MVP) {
            common::Vector2D<double> dim{ 0.8, 0.8 };
            common::Vector2D<double> pos = position;
            auto& mvp = m_ecsWorld.createEntity();
            m_ecsWorld.addSystem<systems::MVPSystem>(engine::definitions::SystemPriority::Low, &m_ecsWorld, mvp.id());
            m_ecsWorld.addComponent<components::DimensionComponent>(mvp, dim);
            m_ecsWorld.addComponent<components::PositionComponent>(mvp, pos);

            auto spriteComponent = map.find("Crown");
            m_ecsWorld.addComponent<components::SpriteComponent>(mvp, spriteComponent->second);
        }
    });

    subscribeInput();
}

void GameState::update(std::chrono::nanoseconds timeStep)
{
    m_world->update(timeStep);
    m_ecsWorld.update(timeStep);
    m_hud->update(timeStep);
}

void GameState::render(engine::IRenderer& renderer)
{
    m_ecsWorld.render(renderer);
    m_hud->render(renderer);
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
    m_inputSubscription = m_inputManager->subscribeAll([&](engine::input::maps::InputMap inputMap, auto&) {
        if (inputMap.hasState(engine::input::Keys::ESCAPE, engine::input::States::PRESSED) || inputMap.hasState(engine::input::Keys::CON_START, engine::input::States::PRESSED)) {
            m_context.next(std::make_unique<PauseMenuState>(m_context));
        }

        if (inputMap.hasState(engine::input::Keys::F2, engine::input::States::PRESSED)) {
            m_context.setSpeed(m_context.speed() - .1);
        }

        if (inputMap.hasState(engine::input::Keys::F3, engine::input::States::PRESSED)) {
            m_context.resetSpeed();
        }

        if (inputMap.hasState(engine::input::Keys::F4, engine::input::States::PRESSED)) {
            m_context.setSpeed(m_context.speed() + .1);
        }
    });
}
}
