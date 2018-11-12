#pragma once

#include "BaseMenuState.h"
#include <engine/game/IGame.h>

#include <chrono>
#include <engine/ui/components/CustomAction.h>
#include <engine/ui/components/IAction.h>

namespace engine::ui {
class Button;
}

namespace game {
class MainMenuState : public BaseMenuState {
    std::shared_ptr<engine::ui::Button> m_startButton;
    std::shared_ptr<engine::ui::Button> m_optionsButton;
    std::shared_ptr<engine::ui::Button> m_quitButton;

public:
    explicit MainMenuState(engine::input::InputManager& inputManager);

    void onStartClick(std::function<void()> action);
    void onOptionsClick(std::function<void()> action);
    void onQuitClick(std::function<void()> action);
};
}
