#include "MainMenuState.h"

#include <engine/ui/components/Button.h>

namespace game {
MainMenuState::MainMenuState(engine::input::InputManager& inputManager)
    : BaseMenuState(inputManager)
{
    m_startButton = std::make_shared<engine::ui::Button>(
        engine::ui::ComponentSize(
            engine::ui::ComponentSizeType::Fit,
            engine::ui::ComponentSizeType::Fit,
            common::Vector2D<double>(1, 1)),
        "START");
    appendComponent(m_startButton);

    m_optionsButton = std::make_shared<engine::ui::Button>(
        engine::ui::ComponentSize(
            engine::ui::ComponentSizeType::Fit,
            engine::ui::ComponentSizeType::Fit,
            common::Vector2D<double>(1, 1)),
        "OPTIONS");
    appendComponent(m_optionsButton);

    m_quitButton = std::make_shared<engine::ui::Button>(
        engine::ui::ComponentSize(
            engine::ui::ComponentSizeType::Fit,
            engine::ui::ComponentSizeType::Fit,
            common::Vector2D<double>(1, 1)),
        "QUIT");
    appendComponent(m_quitButton);
}

void MainMenuState::onStartClick(std::function<void()> action)
{
    std::unique_ptr<engine::ui::IAction> startGameAction = std::make_unique<engine::ui::CustomAction>(action);
    m_startButton->setAction(std::move(startGameAction));
}

void MainMenuState::onOptionsClick(std::function<void()> action)
{
    std::unique_ptr<engine::ui::IAction> optionsAction = std::make_unique<engine::ui::CustomAction>(action);
    m_optionsButton->setAction(std::move(optionsAction));
}

void MainMenuState::onQuitClick(std::function<void()> action)
{
    std::unique_ptr<engine::ui::IAction> quitAction = std::make_unique<engine::ui::CustomAction>(action);
    m_quitButton->setAction(std::move(quitAction));
}
}
