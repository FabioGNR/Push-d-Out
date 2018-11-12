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
PauseMenuState::PauseMenuState(engine::input::InputManager& inputManager)
    : BaseMenuState(inputManager)
{
    m_resumeButton = std::make_shared<engine::ui::Button>(
        engine::ui::ComponentSize(
            engine::ui::ComponentSizeType::Fit,
            engine::ui::ComponentSizeType::Fit,
            common::Vector2D<double>(1, 1)),
        "RESUME");
    appendComponent(m_resumeButton);
}
void PauseMenuState::onResumeClick(std::function<void()> action)
{
    std::unique_ptr<engine::ui::IAction> resumeAction = std::make_unique<engine::ui::CustomAction>(action);
    m_resumeButton->setAction(std::move(resumeAction));
}
} // end namespace game