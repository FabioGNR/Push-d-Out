#include "LevelEditorMenuState.h"
#include "MainMenuState.h"

#include <engine/game/IGame.h>
#include <engine/ui/components/Button.h>
#include <engine/ui/components/CustomAction.h>
#include <engine/ui/components/IAction.h>
#include <game/Game.h>

namespace game {

LevelEditorMenuState::LevelEditorMenuState(level::Editor* editor, engine::IGame& context)
    : BaseMenuState(context)
    , m_editor(editor)
    , m_backgroundOverlay("assets/sprites/ui/radial_overlay.png", { 0, 0 }, { 0, 0 })
{
    auto& game = dynamic_cast<Game&>(m_context);
    m_backgroundOverlay.setSize(game.getScreenSize());
}

void LevelEditorMenuState::render(engine::IRenderer& renderer)
{
    m_editor->draw(renderer);
    renderer.draw(m_backgroundOverlay);
    BaseMenuState::render(renderer);
}

void LevelEditorMenuState::prependButtons(engine::ui::StackPanel& panel)
{
    panel.addComponent(makeStretchedButton("RESUME", [&] {
        m_editor->isActive = true;
        m_context.previous();
    }));

    panel.addComponent(makeStretchedButton("SAVE", [&] {
        m_editor->isActive = true;
        m_editor->showKeyboard(true);
        m_context.previous();
    }));

    panel.addComponent(makeStretchedButton("MAIN MENU", [&] {
        m_editor->isActive = true;
        auto* context = &m_context;
        context->clearStates();
        context->next(std::make_unique<MainMenuState>(*context));
    }));
}

void LevelEditorMenuState::appendButtons(engine::ui::StackPanel& panel)
{
    (void)panel;
}
}
