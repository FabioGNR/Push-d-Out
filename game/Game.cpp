#include "Game.h"
#include <common/Vector2D.h>
#include <events/EventManager.h>
#include <input/InputManager.h>
#include <game/states/GameState.h>
#include <graphics/SDL/SDLRenderer.h>
#include <graphics/drawable/RectangleShape.h>
#include <window/SDLWindow.h>
#include <window/Window.h>

namespace game {
Game::Game(engine::WindowProperties& properties)
    : IGame()
{
    m_window = std::make_unique<engine::SDLWindow>(properties);
    m_eventManager = std::make_unique<engine::events::EventManager>();
    m_renderer = std::make_unique<engine::SDLRenderer>(*(engine::SDLWindow*)m_window.get());
}

void Game::init()
{
}

void Game::onUpdate(std::chrono::nanoseconds timeStep)
{
    if (!m_eventManager->getEvents()) {
        stop();
    }
    m_states.top()->update(timeStep);
}

void Game::onRender()
{
    m_renderer->clear();
    m_states.top()->render(*m_renderer);
    m_renderer->show();
}

const engine::input::InputManager& Game::getInputManager()
{
    return m_eventManager->getInput();
}
}