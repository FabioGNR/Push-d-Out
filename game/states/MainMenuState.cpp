#include "MainMenuState.h"
#include "GameState.h"
#include "game/Game.h"
#include <engine/common/Vector2D.h>
#include <engine/game/IGame.h>
#include <engine/game/State.h>
#include <engine/ui/components/Button.h>
#include <engine/ui/components/CustomAction.h>
#include <engine/ui/components/Label.h>
#include <engine/ui/components/LayoutPanel.h>
#include <engine/ui/components/StackPanel.h>

using namespace std::chrono_literals;

namespace game {
MainMenuState::MainMenuState(engine::IGame& context)
    : BaseMenuState(context)
{
}

void MainMenuState::prependButtons(engine::ui::StackPanel& panel)
{
    std::unique_ptr<engine::ui::IAction> startGameAction = std::make_unique<engine::ui::CustomAction>([&]() {
        m_context.next(std::make_shared<GameState>(m_context));
    });
    auto startButton = std::make_shared<engine::ui::Button>(
        engine::ui::ComponentSize(
            engine::ui::ComponentSizeType::Fit,
            engine::ui::ComponentSizeType::Fit,
            common::Vector2D<double>(1, 1)),
        "START");
    startButton->setAction(std::move(startGameAction));
    panel.addComponent(startButton);
}

void MainMenuState::appendButtons(engine::ui::StackPanel& panel)
{
    (void)panel;
    // nothing here yet
}
}
