#pragma once

#include <engine/events/models/Subscription.h>
#include <engine/game/State.h>
#include <engine/input/KeyMap.h>
#include <engine/ui/UISystem.h>

#include <chrono>
#include <engine/game/IGame.h>

namespace engine::ui {
class Button;
}

namespace game {
class Game;
class MainMenuState : public engine::State {
private:
    Game& m_context;
    std::unique_ptr<engine::ui::UISystem> m_uiSystem;

public:
    explicit MainMenuState(Game& context);

    void init() override;
    void resume() override;
    void pause() override;
    void update(std::chrono::nanoseconds timeStep) override;
    void render(engine::IRenderer& renderer) override;

    void close() override;

private:
    std::shared_ptr<engine::ui::Button> makeStartGameButton() const;
    std::shared_ptr<engine::ui::Button> makeQuitButton() const;
};
}
