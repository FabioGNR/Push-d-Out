#include "MainMenuState.h"
#include "GameState.h"
#include "game/Game.h"
#include <engine/common/Vector2D.h>
#include <engine/game/IGame.h>
#include <engine/game/State.h>
#include <engine/sound/SDL/SDLSoundManager.h>
#include <engine/ui/components/Button.h>
#include <engine/ui/components/CustomAction.h>
#include <engine/ui/components/Label.h>
#include <engine/ui/components/LayoutPanel.h>
#include <engine/ui/components/StackPanel.h>

using namespace std::chrono_literals;

namespace game {
MainMenuState::MainMenuState(engine::IGame& context)
    : BaseMenuState(context)
    , m_soundManager(new engine::sound::SDLSoundManager)
{
}

void MainMenuState::prependButtons(engine::ui::StackPanel& panel)
{
    std::unique_ptr<engine::ui::IAction> startGameAction = std::make_unique<engine::ui::CustomAction>([&]() {
        m_context.next(std::make_shared<GameState>(m_context));
    });
    auto startButton = std::make_unique<engine::ui::Button>(
        engine::ui::ComponentSize(
            engine::ui::ComponentSizeType::Fit,
            engine::ui::ComponentSizeType::Fit,
            common::Vector2D<double>(1, 1)),
        "START");
    startButton->setAction(std::move(startGameAction));
    panel.addComponent(std::move(startButton));
}

void MainMenuState::appendButtons(engine::ui::StackPanel& panel)
{
    (void)panel;
    // nothing here yet
}

void MainMenuState::init()
{
    engine::sound::Music music("assets/sounds/menu.wav");
    m_soundManager->play(music);
    BaseMenuState::init();
}

void MainMenuState::resume()
{
    m_soundManager->resume();
    BaseMenuState::resume();
}

void MainMenuState::pause()
{
    m_soundManager->pause();
    BaseMenuState::pause();
}

void MainMenuState::close()
{
    m_soundManager->pause();
    BaseMenuState::close();
}
}
