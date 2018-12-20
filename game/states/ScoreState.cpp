#include "ScoreState.h"

#include <engine/game/IGame.h>
#include <engine/graphics/Camera.h>
#include <engine/graphics/drawable/Font.h>
#include <engine/physics/PhysicsManager.h>
#include <engine/sound/SDL/SDLSoundManager.h>

#include <game/Game.h>
#include <game/builders/BunnyBuilder.h>
#include <game/builders/CharacterBuilder.h>
#include <game/builders/SpriteBuilder.h>
#include <game/components/AnimationsComponent.h>
#include <game/components/BodyComponent.h>
#include <game/components/DimensionComponent.h>
#include <game/components/PlayerNameComponent.h>
#include <game/components/PositionComponent.h>
#include <game/components/SpriteComponent.h>
#include <game/config/ConfigurationRepository.h>
#include <game/level/Theme.h>
#include <game/level/reader/LevelReader.h>
#include <game/states/GameState.h>
#include <game/states/LevelSelectorState.h>
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

#include <memory>
#include <set>
#include <sstream>

namespace game {
using ScorePair = std::pair<std::string, long double>;
using Comparator = std::function<bool(ScorePair, ScorePair)>;

void ScoreState::update(std::chrono::nanoseconds timeStep)
{
    m_world->update(timeStep);
    m_ecsWorld.update(timeStep);
    m_nsTillNextState -= timeStep;

    using namespace std::chrono_literals;
    if (m_nsTillNextState < 0s) {
        m_context.next(std::make_unique<LevelSelectorState>(m_context));
    }
}

void ScoreState::render(engine::IRenderer& renderer)
{
    m_ecsWorld.render(renderer);

    const static std::string message = " seconds left";
    renderer.draw(
        engine::Font("assets/fonts/Pixeled.ttf",
            std::to_string(std::chrono::duration_cast<std::chrono::seconds>(m_nsTillNextState).count()) + message,
            32,
            engine::Color{ 255, 255, 255, 255 },
            { 100, 100 }));
}

void ScoreState::init()
{
    Comparator compFunctor = [](ScorePair element1, ScorePair element2) {
        return element1.second > element2.second;
    };

    std::set<ScorePair, Comparator> scoreList(m_score.begin(), m_score.end(), compFunctor);

    for (const ScorePair& element : scoreList) {
        std::string name = element.first;
        std::stringstream s;
        auto score = std::round(element.second);

        s << name << " has a score of ";

        if (element == *scoreList.begin()) {
            s << score + 1000 /* bonus points yay */ << " (winner)";
        } else {
            s << score;
        }
    }

    GameState::MVP = scoreList.begin()->first;

    auto& game = dynamic_cast<Game&>(m_context);

    m_soundManager = game.getSoundManager();

    // Read Level based on JSON file
    level::LevelReader lr{};
    auto level = lr.build(lr.parse("assets/winner/win.json"));

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
    m_ecsWorld.addSystem<systems::WeaponSystem>(engine::definitions::SystemPriority::Medium, &m_ecsWorld, m_world.get(), m_inputManager, m_soundManager, &m_camera);
    m_ecsWorld.addSystem<systems::ItemSystem>(engine::definitions::SystemPriority::Medium, m_ecsWorld, *m_world, m_inputManager);
    m_ecsWorld.addSystem<systems::InventorySystem>(engine::definitions::SystemPriority::Medium, m_ecsWorld, m_inputManager);
    m_ecsWorld.addSystem<systems::items::ReverseGravitySystem>(engine::definitions::SystemPriority::Medium, m_ecsWorld, *m_world, m_soundManager);
    m_ecsWorld.addSystem<systems::TeleportSystem>(engine::definitions::SystemPriority::Medium, &m_ecsWorld);
    m_ecsWorld.addSystem<systems::PunchingSystem>(engine::definitions::SystemPriority::Medium, &m_ecsWorld, m_world.get(), m_inputManager, m_soundManager);
    m_ecsWorld.addSystem<systems::VisualEffectSystem>(engine::definitions::SystemPriority::Medium, &m_ecsWorld);
    m_ecsWorld.addSystem<systems::CooldownSystem>(engine::definitions::SystemPriority::Low, m_ecsWorld);
    m_ecsWorld.addSystem<systems::AnimationSystem>(engine::definitions::SystemPriority::Low, &m_ecsWorld, &m_camera);
    m_ecsWorld.addSystem<systems::MovementSystem>(engine::definitions::SystemPriority::Low, m_ecsWorld);
    m_ecsWorld.addSystem<systems::OutOfBoundsCleanUpSystem>(engine::definitions::SystemPriority::Low, &m_ecsWorld, &m_camera);
    m_ecsWorld.addSystem<systems::GarbageCollectorSystem>(engine::definitions::SystemPriority::High, &m_ecsWorld);

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

    initPlayers();
}
void ScoreState::resume()
{
}

void ScoreState::pause()
{
}

void ScoreState::close()
{
}

void ScoreState::initPlayers()
{
    Comparator compFunctor = [](ScorePair element1, ScorePair element2) {
        return element1.second > element2.second;
    };
    std::set<ScorePair, Comparator> scoreList(m_score.begin(), m_score.end(), compFunctor);

    std::vector<engine::ecs::Entity*> inputsToRemove;

    m_ecsWorld.forEachEntityWith<components::PlayerNameComponent, components::PlayerInputComponent>([&](auto& entity) {
        const auto& playerNameComponent = m_ecsWorld.getComponent<components::PlayerNameComponent>(entity);

        if (playerNameComponent.name != scoreList.rbegin()->first) {
            auto& spriteComponent = m_ecsWorld.getComponent<components::SpriteComponent>(entity);
            auto& animations = m_ecsWorld.getComponent<components::AnimationsComponent>(entity).animations;

            const auto& ani = animations.find("Excited");
            if (ani != animations.end()) {
                spriteComponent = ani->second;
                spriteComponent.loops = true;
            }
            inputsToRemove.push_back(&entity);
        }
    });

    auto positions = builders::CharacterSpawnGenerator::collect(m_ecsWorld);
    auto loserIt = std::min_element(positions.begin(), positions.end(), [](const auto& a, const auto& b) {
        return a.x < b.x;
    });
    auto loserPos = *loserIt;
    positions.erase(loserIt);
    std::sort(positions.begin(), positions.end(), [](const auto& a, const auto& b) {
        return a.y > b.y;
    });

    int position = 0;

    engine::physics::Body* winnerBody = nullptr;
    m_ecsWorld.forEachEntityWith<components::PlayerNameComponent, components::PlayerInputComponent>([&](auto& entity) {
        const auto& playerNameComponent = m_ecsWorld.getComponent<components::PlayerNameComponent>(entity);
        auto& body = *m_ecsWorld.getComponent<components::BodyComponent>(entity).body;

        if (playerNameComponent.name == GameState::MVP) {
            winnerBody = &body;
        }

        if (playerNameComponent.name == scoreList.rbegin()->first) {
            body.setPosition(loserPos);
        } else {
            body.setPosition(positions[position++]);
        }
    });

    m_ecsWorld.forEachEntityWith<components::PlayerNameComponent>([&](auto& entity) {
        auto& nameComp = m_ecsWorld.getComponent<components::PlayerNameComponent>(entity);
        if (m_score.count(nameComp.name) != 0) {
            if (nameComp.name == GameState::MVP) {
                nameComp.name += " - " + std::to_string(static_cast<int>(m_score[nameComp.name] * 1000) + 500);
            } else {
                nameComp.name += " - " + std::to_string(static_cast<int>(m_score[nameComp.name] * 1000));
            }
        }
    });

    for (auto* entity : inputsToRemove) {
        m_ecsWorld.removeComponent<components::PlayerInputComponent>(*entity);
    }

    addExplosion(winnerBody->getPosition());
}
void ScoreState::addExplosion(const common::Vector2D<double>& pos)
{
    std::string basePath{ "assets/sprites/" };
    std::string baseThemePath{ basePath + "themes/" };

    builders::SpriteBuilder miscSpriteBuilder{ basePath + "misc/explosion.png", basePath + "misc/explosion.json" };
    auto miscSpriteComponentMap = miscSpriteBuilder.build();

    auto& entity = m_ecsWorld.createEntity();
    auto posComponent = components::PositionComponent(pos - common::Vector2D<double>(3, 2));
    m_ecsWorld.addComponent<components::PositionComponent>(entity, posComponent);
    // Add a dimension component to equipment spawn entity
    auto dimensionComponent = components::DimensionComponent(common::Vector2D<double>(10, 10));
    m_ecsWorld.addComponent<components::DimensionComponent>(entity, dimensionComponent);

    // Add a sprite component to equipment spawn entity
    auto spriteComponentPair = miscSpriteComponentMap.find("explosion");
    if (spriteComponentPair != miscSpriteComponentMap.end()) {
        auto spriteComponent = spriteComponentPair->second;
        spriteComponent.loops = true;
        m_ecsWorld.addComponent<components::SpriteComponent>(entity, spriteComponent);
    }
}
}
