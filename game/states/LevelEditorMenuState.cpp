#include "LevelEditorMenuState.h"
#include "MainMenuState.h"

#include <engine/game/IGame.h>
#include <engine/ui/components/Button.h>
#include <engine/ui/components/CustomAction.h>
#include <engine/ui/components/IAction.h>

namespace game {

LevelEditorMenuState::LevelEditorMenuState(level::Editor* editor, engine::IGame& context)
    : BaseMenuState(context)
    , m_editor(editor)
{
}

void LevelEditorMenuState::prependButtons(engine::ui::StackPanel& panel)
{
    std::unique_ptr<engine::ui::IAction> resumeEditorAction = std::make_unique<engine::ui::CustomAction>([&]() {
        m_context.previous();
    });

    auto resumeButton = std::make_unique<engine::ui::Button>(
        engine::ui::ComponentSize(
            engine::ui::ComponentSizeType::Stretch,
            engine::ui::ComponentSizeType::Fit,
            common::Vector2D<double>(1, 1)),
        "RESUME");

    resumeButton->setAction(std::move(resumeEditorAction));
    panel.addComponent(std::move(resumeButton));

    std::unique_ptr<engine::ui::IAction> saveLevelAction = std::make_unique<engine::ui::CustomAction>([&]() {
        m_editor->showKeyboard(true);
        m_context.previous();
    });

    auto saveButton = std::make_unique<engine::ui::Button>(
        engine::ui::ComponentSize(
            engine::ui::ComponentSizeType::Stretch,
            engine::ui::ComponentSizeType::Fit,
            common::Vector2D<double>(1, 1)),
        "SAVE");

    saveButton->setAction(std::move(saveLevelAction));
    panel.addComponent(std::move(saveButton));

    std::unique_ptr<engine::ui::IAction> mainMenuAction = std::make_unique<engine::ui::CustomAction>([&]() {
        auto* context = &m_context;
        context->clearStates();
        context->next(std::make_unique<MainMenuState>(*context));
    });

    auto mainMenuButton = std::make_unique<engine::ui::Button>(
        engine::ui::ComponentSize(
            engine::ui::ComponentSizeType::Stretch,
            engine::ui::ComponentSizeType::Fit,
            common::Vector2D<double>(1, 1)),
        "MAIN MENU");
    mainMenuButton->setAction(std::move(mainMenuAction));
    panel.addComponent(std::move(mainMenuButton));
}

void LevelEditorMenuState::appendButtons(engine::ui::StackPanel& panel)
{
    (void)panel;
}
}
