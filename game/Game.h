#pragma once

#include <engine/common/Vector2D.h>
#include <engine/events/EventManager.h>
#include <engine/game/IGame.h>
#include <engine/game/State.h>
#include <engine/graphics/SDL/SDLRenderer.h>
#include <engine/sound/ISoundManager.h>
#include <engine/window/Window.h>
#include <game/config/Configuration.h>
#include <memory>
#include <stack>

namespace game {
class Game : public engine::IGame {
private:
    std::unique_ptr<engine::Window> m_window;
    std::unique_ptr<engine::IRenderer> m_renderer;
    std::unique_ptr<engine::events::EventManager> m_eventManager;
    std::unique_ptr<engine::sound::ISoundManager> m_soundManager;

    void applyConfig();

public:
    static bool DEBUG;
    explicit Game(engine::WindowProperties& properties);

    void init() override;
    void onUpdate(std::chrono::nanoseconds timeStep) override;
    void onRender() override;
    void applyConfig(const config::Configuration& config);

    engine::Window& window() const;
    common::Vector2D<int> getScreenSize() const;
    engine::input::InputManager* getInputManager();
    engine::sound::ISoundManager* getSoundManager();
};
}
