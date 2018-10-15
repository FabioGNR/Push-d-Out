#include "GameState.h"
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
    // Read level based on JSON file
    auto level = game::levelReader::getLevel(game::levelReader::readJSON("assets/levels/base-level.json"));
    game::levelReader::createEntities(m_ecsWorld, *m_world, level);

    m_ecsWorld.addSystem<systems::RenderSystem>(
        engine::definitions::SystemPriority::Medium, m_ecsWorld, UNIT_SIZE * UNIT_MULTIPLIER);
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
