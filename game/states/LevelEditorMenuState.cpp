#include "LevelEditorMenuState.h"

#include <engine/game/IGame.h>
#include <engine/ui/components/Button.h>
#include <engine/ui/components/CustomAction.h>
#include <engine/ui/components/IAction.h>

namespace game {

LevelEditorMenuState::LevelEditorMenuState(engine::IGame& context)
    : BaseMenuState(context)
{
}

void LevelEditorMenuState::prependButtons(engine::ui::StackPanel& panel)
{
    std::unique_ptr<engine::ui::IAction> resumeEditorAction = std::make_unique<engine::ui::CustomAction>([&]() {
        m_context.previous();
    });

    auto resumeButton = std::make_unique<engine::ui::Button>(
        engine::ui::ComponentSize(
            engine::ui::ComponentSizeType::Fit,
            engine::ui::ComponentSizeType::Fit,
            common::Vector2D<double>(1, 1)),
        "RESUME");

    resumeButton->setAction(std::move(resumeEditorAction));
    panel.addComponent(std::move(resumeButton));
}

void LevelEditorMenuState::appendButtons(engine::ui::StackPanel& panel)
{
    (void)panel;
}
}
