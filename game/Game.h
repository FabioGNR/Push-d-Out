#pragma once

#include <engine/common/Vector2D.h>
#include <engine/events/EventManager.h>
#include <engine/game/IGame.h>
#include <engine/game/State.h>
#include <engine/graphics/SDL/SDLRenderer.h>
#include <engine/window/Window.h>
#include <memory>
#include <stack>

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

    engine::Window& window() const;
    common::Vector2D<int> getScreenSize() const;
    engine::input::InputManager& getInputManager();
};
}
