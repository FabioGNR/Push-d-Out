#pragma once

#include <events/EventManager.h>
#include <game/IGame.h>
#include <game/State.h>
#include <graphics/SDL/SDLRenderer.h>
#include <memory>
#include <stack>
#include <window/Window.h>

namespace game {
class Game : public engine::IGame {
private:
    std::unique_ptr<engine::Window> m_window;
    std::unique_ptr<engine::IRenderer> m_renderer;
    std::unique_ptr<engine::events::EventManager> m_eventManager;

public:
    explicit Game(engine::WindowProperties& properties);

    void init() override;
    void onUpdate(std::chrono::nanoseconds timeStep) override;
    void onRender() override;

    engine::input::InputManager& getInputManager();
};
}
