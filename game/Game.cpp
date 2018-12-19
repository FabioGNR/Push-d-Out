#include "Game.h"
#include <engine/common/Vector2D.h>
#include <engine/events/EventManager.h>
#include <engine/events/SDLEventHandler.h>
#include <engine/graphics/SDL/SDLRenderer.h>
#include <engine/graphics/drawable/RectangleShape.h>
#include <engine/sound/SDL/SDLSoundManager.h>
#include <engine/window/SDLWindow.h>
#include <engine/window/Window.h>
#include <game/config/ConfigurationRepository.h>

namespace game {
bool Game::DEBUG = false; // Init var

Game::Game(engine::WindowProperties& properties)
{
    m_window = std::make_unique<engine::SDLWindow>(properties);
    m_eventManager = std::make_unique<engine::events::EventManager>(std::make_unique<engine::events::SDLEventHandler>());
    m_renderer = std::make_unique<engine::SDLRenderer>(
        *dynamic_cast<engine::SDLWindow*>(m_window.get()));
    m_soundManager = std::make_unique<engine::sound::SDLSoundManager>();
}

void Game::init()
{
    applyConfig();
}

void Game::onUpdate(std::chrono::nanoseconds timeStep)
{
    m_eventManager->getInput()->notifyAll();
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

engine::input::InputManager* Game::getInputManager()
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

engine::sound::ISoundManager* Game::getSoundManager()
{
    return m_soundManager.get();
}

void Game::applyConfig()
{
    const auto& config = config::ConfigurationRepository::get();
    applyConfig(config);
}

void Game::applyConfig(const config::Configuration& config)
{
    const auto volumeScalar = config.sound.masterVolume / 100.0;
    // set music volume lower than sfx volume (max is 80%)
    m_soundManager->setMusicVolume(engine::sound::Volume(static_cast<int>(config.sound.musicVolume * volumeScalar * 0.8)));
    m_soundManager->setSfxVolume(engine::sound::Volume(static_cast<int>(config.sound.sfxVolume * volumeScalar * 0.8)));
}
}
