#include "Game.h"
#include <engine/common/Vector2D.h>
#include <engine/events/EventManager.h>
#include <engine/events/SDLEventHandler.h>
#include <engine/graphics/SDL/SDLRenderer.h>
#include <engine/graphics/drawable/RectangleShape.h>
#include <engine/window/SDLWindow.h>
#include <engine/window/Window.h>

namespace game {
Game::Game(engine::WindowProperties& properties)
{
    m_window = std::make_unique<engine::SDLWindow>(properties);
    m_eventManager = std::make_unique<engine::events::EventManager>(std::make_unique<engine::events::SDLEventHandler>());
    m_renderer = std::make_unique<engine::SDLRenderer>(
        *dynamic_cast<engine::SDLWindow*>(m_window.get()));
}

void Game::init()
{
}

void Game::onUpdate(std::chrono::nanoseconds timeStep)
{
    m_eventManager->getInput().notifyAll();
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

engine::input::InputManager& Game::getInputManager()
{
    return m_eventManager->getInput();
}

common::Vector2D<int> Game::getScreenSize() const
{
    return m_window->getDimensions();
}

engine::Window& Game::window() const
{
    return *m_window;
}
}
