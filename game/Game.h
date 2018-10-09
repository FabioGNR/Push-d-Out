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
    std::unique_ptr<engine::EventManager> m_eventManager;
    std::unique_ptr<engine::SDLRenderer> m_renderer;

    std::stack<std::shared_ptr<engine::State>> m_states;

public:
    explicit Game(engine::WindowProperties& properties);

    void next(std::shared_ptr<engine::State> state);
    void previous();

    void onInit() override;
    void onUpdate(std::chrono::nanoseconds timeStep) override;
    void onRender() override;
};
}
