#include "PauseMenuState.h"
#include "GameState.h"
#include "MainMenuState.h"
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
PauseMenuState::PauseMenuState(engine::IGame& context)
    : BaseMenuState(context)
{
}

void PauseMenuState::prependButtons(engine::ui::StackPanel& panel)
{
    const auto& buttonSize = engine::ui::ComponentSize(
        engine::ui::ComponentSizeType::Stretch,
        engine::ui::ComponentSizeType::Fit);
    std::unique_ptr<engine::ui::IAction> resumeGameAction = std::make_unique<engine::ui::CustomAction>([&]() {
        m_context.previous();
    });
    auto resumeButton = std::make_unique<engine::ui::Button>(buttonSize,
        "RESUME");
    resumeButton->setAction(std::move(resumeGameAction));
    panel.addComponent(std::move(resumeButton));
}

void PauseMenuState::appendButtons(engine::ui::StackPanel& panel)
{
    const auto& buttonSize = engine::ui::ComponentSize(
        engine::ui::ComponentSizeType::Stretch,
        engine::ui::ComponentSizeType::Fit);
    std::unique_ptr<engine::ui::IAction> mainMenuAction = std::make_unique<engine::ui::CustomAction>([&]() {
        auto* context = &m_context;
        context->clearStates();
        context->next(std::make_unique<MainMenuState>(*context));
    });

    auto mainMenuButton = std::make_unique<engine::ui::Button>(buttonSize, "MAIN MENU");
    mainMenuButton->setAction(std::move(mainMenuAction));
    panel.addComponent(std::move(mainMenuButton));
}
}