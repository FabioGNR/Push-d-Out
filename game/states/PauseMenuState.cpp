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
    auto resumeButton = std::make_unique<engine::ui::Button>(buttonSize,
        "RESUME");
    resumeButton->setAction(std::make_unique<engine::ui::CustomAction>([&]() {
        m_context.previous();
    }));
    panel.addComponent(std::move(resumeButton));
}

void PauseMenuState::appendButtons(engine::ui::StackPanel& panel)
{
    const auto& buttonSize = engine::ui::ComponentSize(
        engine::ui::ComponentSizeType::Stretch,
        engine::ui::ComponentSizeType::Fit);

    auto mainMenuButton = std::make_unique<engine::ui::Button>(buttonSize, "MAIN MENU");
    mainMenuButton->setAction(std::make_unique<engine::ui::CustomAction>([&]() {
        auto* context = &m_context;
        context->clearStates();
        context->next(std::make_unique<MainMenuState>(*context));
    }));
    panel.addComponent(std::move(mainMenuButton));
}
}