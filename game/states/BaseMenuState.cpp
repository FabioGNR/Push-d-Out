#include "BaseMenuState.h"
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
BaseMenuState::BaseMenuState(engine::IGame& context)
    : engine::State(context)
{
    auto& game = dynamic_cast<Game&>(m_context);
    m_uiSystem = std::make_unique<engine::ui::UISystem>(game.getInputManager());
}

void BaseMenuState::init()
{
    auto rootLayout = std::make_unique<engine::ui::LayoutPanel>(
        engine::ui::ComponentSize(
            engine::ui::ComponentSizeType::Fit, engine::ui::ComponentSizeType::Stretch,
            common::Vector2D<double>(1, 1)),
        engine::ui::FlowDirection::Horizontal);
    auto centerLayout = std::make_unique<engine::ui::LayoutPanel>(
        engine::ui::ComponentSize(
            engine::ui::ComponentSizeType::Fit,
            engine::ui::ComponentSizeType::Fit,
            common::Vector2D<double>(1, 1)),
        engine::ui::FlowDirection::Vertical);
    auto buttonStack = std::make_unique<engine::ui::StackPanel>(
        engine::ui::ComponentSize(
            engine::ui::ComponentSizeType::Fit,
            engine::ui::ComponentSizeType::Fit,
            common::Vector2D<double>(1, 1)),
        engine::ui::FlowDirection::Vertical);
    auto nameLabel = std::make_unique<engine::ui::Label>(
        engine::ui::ComponentSize(
            engine::ui::ComponentSizeType::Fit,
            engine::ui::ComponentSizeType::Fit,
            common::Vector2D<double>(1, 1)),
        "PUSH'D OUT!");
    buttonStack->addComponent(std::move(nameLabel));
    std::unique_ptr<engine::ui::IAction> resumeGameAction = std::make_unique<engine::ui::CustomAction>([&]() {
        m_context.previous();
    });

    prependButtons(*buttonStack);

    auto optionsButton = std::make_unique<engine::ui::Button>(
        engine::ui::ComponentSize(
            engine::ui::ComponentSizeType::Fit,
            engine::ui::ComponentSizeType::Fit,
            common::Vector2D<double>(1, 1)),
        "OPTIONS");
    buttonStack->addComponent(std::move(optionsButton));

    std::unique_ptr<engine::ui::IAction> quitAction = std::make_unique<engine::ui::CustomAction>([&]() {
        m_context.stop();
    });

    auto quitButton = std::make_unique<engine::ui::Button>(
        engine::ui::ComponentSize(
            engine::ui::ComponentSizeType::Fit,
            engine::ui::ComponentSizeType::Fit,
            common::Vector2D<double>(1, 1)),
        "QUIT");
    quitButton->setAction(std::move(quitAction));

    appendButtons(*buttonStack);

    buttonStack->addComponent(std::move(quitButton));
    centerLayout->addComponent(std::move(buttonStack), engine::ui::LayoutAnchor::Center);
    rootLayout->addComponent(std::move(centerLayout), engine::ui::LayoutAnchor::Center);
    auto frame = engine::ui::Frame(std::move(rootLayout));
    m_uiSystem->push(std::move(frame));
}

void BaseMenuState::update(std::chrono::nanoseconds /* timeStep */)
{
}

void BaseMenuState::render(engine::IRenderer& renderer)
{
    m_uiSystem->draw(renderer, common::Vector2D<int>(1280, 768));
}

void BaseMenuState::resume()
{
    m_uiSystem->setActive(true);
}

void BaseMenuState::pause()
{
    m_uiSystem->setActive(false);
}

void BaseMenuState::close()
{
    m_uiSystem->setActive(false);
}
}
