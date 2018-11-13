#include "PauseMenuState.h"
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
PauseMenuState::PauseMenuState(engine::IGame& context)
    : BaseMenuState(context)
{
}

void PauseMenuState::prependButtons(engine::ui::StackPanel& panel)
{
    std::unique_ptr<engine::ui::IAction> resumeGameAction = std::make_unique<engine::ui::CustomAction>([&]() {
        m_context.previous();
    });

    auto resumeButton = std::make_unique<engine::ui::Button>(
        engine::ui::ComponentSize(
            engine::ui::ComponentSizeType::Fit,
            engine::ui::ComponentSizeType::Fit,
            common::Vector2D<double>(1, 1)),
        "RESUME");
    resumeButton->setAction(std::move(resumeGameAction));
    panel.addComponent(std::move(resumeButton));
}

void PauseMenuState::appendButtons(engine::ui::StackPanel& panel)
{
    (void)panel;
    // nothing here yet
}
}