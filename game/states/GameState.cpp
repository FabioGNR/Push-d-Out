#include "GameState.h"
#include "game/systems/CameraSystem.h"
#include "game/systems/RenderSystem.h"
#include <engine/physics/Body.h>
#include <game/components/DimensionComponent.h>
#include <game/components/PositionComponent.h>
#include <game/components/SpriteComponent.h>
#include <game/themes/Earth.h>
#include <graphics/Color.h>
#include <graphics/drawable/RectangleShape.h>
#include <iostream>
#include <random>
#include <game/Game.h>

#include "game/level/levelReader/LevelReader.h"

namespace game {
GameState::GameState(engine::IGame& game)
    : engine::State(game)
{
    m_physicsManager = std::make_unique<engine::physics::PhysicsManager>();
    themes::Theme theme = themes::Earth{};
    m_world = m_physicsManager->createWorld(common::Vector2D<int>(40, 24), theme.getGravity(), theme.getFriction());
}

void GameState::init()
{
    Game& game = dynamic_cast<Game&>(m_context);
    // Read level based on JSON file
    auto level = game::levelReader::getLevel(game::levelReader::readJSON("assets/levels/base-level.json"));
    game::levelReader::createEntities(m_ecsWorld, *m_world, level);

    auto camera = std::make_shared<engine::graphics::Camera>(UNIT_MULTIPLIER * UNIT_SIZE, game.getScreenSize());
    m_ecsWorld.addSystem<systems::CameraSystem>(engine::definitions::SystemPriority::Medium,
        camera);

    m_ecsWorld.addSystem<systems::RenderSystem>(
        engine::definitions::SystemPriority::Medium, m_ecsWorld, camera);
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
}
