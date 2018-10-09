#include "GameState.h"
#include <engine/physics/Body.h>
#include <game/themes/Earth.h>
#include <graphics/Color.h>
#include <graphics/drawable/RectangleShape.h>
#include <iostream>

#include "game/level/levelReader/LevelReader.h"

namespace game {
GameState::GameState() : State()
{
    m_physicsManager = std::make_unique<engine::physics::PhysicsManager>(UNIT_SIZE * UNIT_MULTIPLIER);

    themes::Theme theme = themes::Earth{};
    m_world = m_physicsManager->createWorld(common::Vector2D(25, 15), theme.getGravity(), theme.getFriction());

    // ground
    m_world->createStaticBody(0, 0, 100, 1);

    // falls out of the sky
    m_world->createDynamicBody(10, 20, 1, 2);
    m_world->createDynamicBody(5, 10, 1, 2);
    m_world->createDynamicBody(20, 50, 1, 2);
    m_world->createDynamicBody(9, 30, 2, 2);

    json j = game::levelReader::readJSON("assets\\levels\\base_level.JSON");
    std::cout << "JSON: " << j << std::endl;
    level l = game::levelReader::getLevel(j);
    std::cout << "level: " << l.name << std::endl;
    engine::ecs::World ecsWorld = game::levelReader::createEntities(l);
}

void GameState::update(std::chrono::nanoseconds timeStep)
{
    m_world->update(timeStep);
}

void GameState::render(engine::IRenderer &renderer)
{
    for (const auto body : m_world->getBodies()) {
        common::Vector2D pos = body->getPosition();
        common::Vector2D size = body->getDimensions();

        engine::RectangleShape shape(pos.x, pos.y, size.x, size.y, engine::Color{ 255, 255, 255, 100 });
        renderer.draw(shape);
    }
}
}
