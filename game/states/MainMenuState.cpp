#include "MainMenuState.h"
#include "GameState.h"
#include "game/Game.h"
#include <engine/common/Vector2D.h>
#include <engine/game/IGame.h>
#include <engine/game/State.h>
#include <engine/ui/components/Button.h>
#include <engine/ui/components/Label.h>
#include <engine/ui/components/LayoutPanel.h>
#include <engine/ui/components/StackPanel.h>

using namespace std::chrono_literals;

namespace game {
MainMenuState::MainMenuState(engine::IGame& game)
    : engine::State(game)
{
    m_system = std::make_unique<engine::ui::UISystem>();

    dynamic_cast<Game&>(game).getInputManager()->subscribe(this);
}

void MainMenuState::init()
{
    auto rootLayout = std::make_shared<engine::ui::LayoutPanel>(
        engine::ui::ComponentSize(
            engine::ui::ComponentSizeType::Fit, engine::ui::ComponentSizeType::Stretch,
            common::Vector2D(1, 1)),
        engine::ui::FlowDirection::Horizontal);
    auto centerLayout = std::make_shared<engine::ui::LayoutPanel>(
        engine::ui::ComponentSize(
            engine::ui::ComponentSizeType::Fit,
            engine::ui::ComponentSizeType::Fit,
            common::Vector2D(1, 1)),
        engine::ui::FlowDirection::Vertical);
    rootLayout->addComponent(centerLayout, engine::ui::LayoutAnchor::Center);
    auto buttonStack = std::make_shared<engine::ui::StackPanel>(
        engine::ui::ComponentSize(
            engine::ui::ComponentSizeType::Fit,
            engine::ui::ComponentSizeType::Fit,
            common::Vector2D(1, 1)),
        engine::ui::FlowDirection::Vertical);
    centerLayout->addComponent(buttonStack, engine::ui::LayoutAnchor::Center);
    auto nameLabel = std::make_shared<engine::ui::Label>(
        engine::ui::ComponentSize(
            engine::ui::ComponentSizeType::Fit,
            engine::ui::ComponentSizeType::Fit,
            common::Vector2D(1, 1)),
        "PUSH'D OUT!");
    buttonStack->addComponent(nameLabel);
    auto startButton = std::make_shared<engine::ui::Button>(
        engine::ui::ComponentSize(
            engine::ui::ComponentSizeType::Fit,
            engine::ui::ComponentSizeType::Fit,
            common::Vector2D(1, 1)),
        "START");
    buttonStack->addComponent(startButton);
    auto optionsButton = std::make_shared<engine::ui::Button>(
        engine::ui::ComponentSize(
            engine::ui::ComponentSizeType::Fit,
            engine::ui::ComponentSizeType::Fit,
            common::Vector2D(1, 1)),
        "OPTIONS");
    buttonStack->addComponent(optionsButton);
    auto quitButton = std::make_shared<engine::ui::Button>(
        engine::ui::ComponentSize(
            engine::ui::ComponentSizeType::Fit,
            engine::ui::ComponentSizeType::Fit,
            common::Vector2D(1, 1)),
        "QUIT");
    buttonStack->addComponent(quitButton);
    auto frame = engine::ui::Frame(rootLayout);
    m_system->push(frame);
}

void MainMenuState::update(std::chrono::nanoseconds /* timeStep */)
{
    // check if map contains input for 'SPACE'
    if (m_keymap.find(engine::input::SPACE) != m_keymap.end()) {
        m_context.next(std::make_shared<GameState>(m_context));
    }
}

void MainMenuState::render(engine::IRenderer& renderer)
{
    auto uiRenderer = engine::ui::UIRenderer{ renderer };
    m_system->draw(uiRenderer, common::Vector2D(1280, 768));
}

void MainMenuState::onInputUpdate(std::map<engine::input::Keys, engine::events::IControlEvent*>& keyMap)
{
    m_keymap = keyMap;
}
}
