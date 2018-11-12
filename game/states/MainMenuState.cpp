#include "MainMenuState.h"
#include "GameState.h"
#include "game/Game.h"
#include "game/themes/Earth.h"

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
MainMenuState::MainMenuState(Game& context)
    : m_context(context)
{
    m_uiSystem = std::make_unique<engine::ui::UISystem>(m_context.getInputManager());
}

void MainMenuState::init()
{
    // Create root layout
    auto rootLayout = std::make_shared<engine::ui::LayoutPanel>(
        engine::ui::ComponentSize(
            engine::ui::ComponentSizeType::Fit, engine::ui::ComponentSizeType::Stretch,
            common::Vector2D<double>(1, 1)),
        engine::ui::FlowDirection::Horizontal);
    auto centerLayout = std::make_shared<engine::ui::LayoutPanel>(
        engine::ui::ComponentSize(
            engine::ui::ComponentSizeType::Fit,
            engine::ui::ComponentSizeType::Fit,
            common::Vector2D<double>(1, 1)),
        engine::ui::FlowDirection::Vertical);
    rootLayout->addComponent(centerLayout, engine::ui::LayoutAnchor::Center);
    auto buttonStack = std::make_shared<engine::ui::StackPanel>(
        engine::ui::ComponentSize(
            engine::ui::ComponentSizeType::Fit,
            engine::ui::ComponentSizeType::Fit,
            common::Vector2D<double>(1, 1)),
        engine::ui::FlowDirection::Vertical);
    centerLayout->addComponent(buttonStack, engine::ui::LayoutAnchor::Center);

    // Add Game label
    auto nameLabel = std::make_shared<engine::ui::Label>(
        engine::ui::ComponentSize(
            engine::ui::ComponentSizeType::Fit,
            engine::ui::ComponentSizeType::Fit,
            common::Vector2D<double>(1, 1)),
        "PUSH'D OUT!");
    buttonStack->addComponent(nameLabel);

    auto startButton = makeStartGameButton();
    buttonStack->addComponent(startButton);

    auto optionsButton = std::make_shared<engine::ui::Button>(
        engine::ui::ComponentSize(
            engine::ui::ComponentSizeType::Fit,
            engine::ui::ComponentSizeType::Fit,
            common::Vector2D<double>(1, 1)),
        "OPTIONS");
    buttonStack->addComponent(optionsButton);

    auto quitButton = makeQuitButton();
    buttonStack->addComponent(quitButton);

    auto frame = engine::ui::Frame(rootLayout);
    m_uiSystem->push(frame);
}
std::shared_ptr<engine::ui::Button> MainMenuState::makeQuitButton() const
{
    auto quitAction = std::make_unique<engine::ui::CustomAction>([&]() {
        m_context.stop();
    });

    auto quitButton = std::make_shared<engine::ui::Button>(
        engine::ui::ComponentSize(
            engine::ui::ComponentSizeType::Fit,
            engine::ui::ComponentSizeType::Fit,
            common::Vector2D<double>(1, 1)),
        "QUIT");
    quitButton->setAction(move(quitAction));

    return quitButton;
}
std::shared_ptr<engine::ui::Button> MainMenuState::makeStartGameButton() const
{
    // Make the new game
    // TODO: Game is made with hard-coded options. Make sure we get our options from somewhere else

    /*
    // Set up input delegate
    gameState->onInput([&](engine::input::KeyMap keyMap, auto&) {
        if (keyMap.hasKeyState(engine::input::Keys::ESCAPE, engine::input::KeyStates::PRESSED)) {
            m_context.previous();
        }
    });
     */

    // make the start button
    auto startButton = std::make_shared<engine::ui::Button>(
        engine::ui::ComponentSize(
            engine::ui::ComponentSizeType::Fit,
            engine::ui::ComponentSizeType::Fit,
            common::Vector2D<double>(1, 1)),
        "START");

    // Set up button action
    auto startGameAction = std::make_unique<engine::ui::CustomAction>([&]() {
      auto gameState = std::make_shared<GameState>(
          m_context.getScreenSize(),
          themes::Earth{},
          std::make_unique<engine::sound::SDLSoundManager>(),
          m_context.getInputManager());
        m_context.next(gameState);
    });
    startButton->setAction(move(startGameAction));

    return startButton;
}

void MainMenuState::update(std::chrono::nanoseconds /* timeStep */)
{
}

void MainMenuState::render(engine::IRenderer& renderer)
{
    m_uiSystem->draw(renderer, common::Vector2D<int>(1280, 768));
}

void MainMenuState::resume()
{
    m_uiSystem->setActive(true);
}

void MainMenuState::pause()
{
    m_uiSystem->setActive(false);
}

void MainMenuState::close()
{
    m_uiSystem->setActive(false);
}
}
