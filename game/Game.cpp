#include "Game.h"
#include <common/Vector2D.h>
#include <events/EventManager.h>
#include <events/SDLEventManager.h>
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
    m_eventManager = std::make_unique<engine::SDLEventManager>();
    m_renderer = std::make_unique<engine::SDLRenderer>(*(engine::SDLWindow*)m_window.get());
}

void Game::onInit()
{
}

void Game::onUpdate(std::chrono::nanoseconds timeStep)
{
    if (!m_eventManager->processEvents()) {
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

void Game::previous()
{
    m_states.pop();
    if (m_states.empty()) {
        stop();
    }
}

void Game::next(std::shared_ptr<engine::State> state) {
    m_states.push(state);
}
}
