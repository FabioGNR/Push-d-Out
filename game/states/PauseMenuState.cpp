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
    , m_backgroundOverlay("assets/sprites/ui/radial_overlay.png", { 0, 0 }, { 0, 0 })
{
    auto& game = dynamic_cast<Game&>(m_context);
    m_backgroundOverlay.setSize(game.getScreenSize());
}

void PauseMenuState::prependButtons(engine::ui::StackPanel& panel)
{
    panel.addComponent(makeStretchedButton("RESUME", [&] {
        m_context.previous();
    }));
}

void PauseMenuState::appendButtons(engine::ui::StackPanel& panel)
{
    panel.addComponent(makeStretchedButton("MAIN MENU", [&] {
        auto* context = &m_context;
        context->clearStates();
        context->next(std::make_unique<MainMenuState>(*context));
    }));
}

void PauseMenuState::render(engine::IRenderer& renderer)
{
    m_context.getPreviousStateByIndex(1)->render(renderer);
    renderer.draw(m_backgroundOverlay);
    BaseMenuState::render(renderer);
}
}