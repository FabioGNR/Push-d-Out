#include "BaseMenuState.h"
#include "GameState.h"
#include "game/Game.h"
#include <engine/common/Vector2D.h>
#include <engine/game/IGame.h>
#include <engine/game/State.h>
#include <engine/ui/components/Button.h>
#include <engine/ui/components/CustomAction.h>
#include <engine/ui/components/Image.h>
#include <engine/ui/components/Label.h>
#include <engine/ui/components/LayoutPanel.h>
#include <engine/ui/components/StackPanel.h>
#include <engine/ui/components/TextComponent.h>

using namespace std::chrono_literals;

namespace game {
BaseMenuState::BaseMenuState(engine::IGame& context)
    : engine::State(context)
{
    auto& game = dynamic_cast<Game&>(m_context);
    m_screenSize = game.getScreenSize();
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
            engine::ui::ComponentSizeType::Stretch,
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
            engine::ui::ComponentSizeType::Stretch,
            engine::ui::ComponentSizeType::Fit,
            common::Vector2D<double>(1, 1)),
        "OPTIONS");
    buttonStack->addComponent(std::move(optionsButton));

    auto helpButton = std::make_unique<engine::ui::Button>(
        engine::ui::ComponentSize(
            engine::ui::ComponentSizeType::Stretch,
            engine::ui::ComponentSizeType::Fit,
            common::Vector2D<double>(1, 1)),
        "HELP");

    helpButton->setAction(std::make_unique<engine::ui::CustomAction>([&]() {
        openHelpMenu();
    }));
    buttonStack->addComponent(std::move(helpButton));

    std::unique_ptr<engine::ui::IAction> quitAction = std::make_unique<engine::ui::CustomAction>([&]() {
        m_context.stop();
    });

    auto quitButton = std::make_unique<engine::ui::Button>(
        engine::ui::ComponentSize(
            engine::ui::ComponentSizeType::Stretch,
            engine::ui::ComponentSizeType::Fit,
            common::Vector2D<double>(1, 1)),
        "QUIT");
    quitButton->setAction(std::move(quitAction));

    appendButtons(*buttonStack);

    buttonStack->addComponent(std::move(quitButton));

    auto banner = std::make_unique<engine::ui::Image>(
        engine::ui::ComponentSize(
            engine::ui::ComponentSizeType::Stretch,
            engine::ui::ComponentSizeType::Stretch),
        "assets/sprites/advertisement.png");

    auto centerButtonLayout = std::make_unique<engine::ui::LayoutPanel>(
        engine::ui::ComponentSize(
            engine::ui::ComponentSizeType::Fit,
            engine::ui::ComponentSizeType::Fit,
            common::Vector2D<double>(1, 1)),
        engine::ui::FlowDirection::Horizontal);
    centerButtonLayout->addComponent(std::move(buttonStack), engine::ui::LayoutAnchor::Center);
    centerLayout->addComponent(std::move(centerButtonLayout), engine::ui::LayoutAnchor::Center);

    centerLayout->addComponent(std::move(banner), engine::ui::LayoutAnchor::End);
    rootLayout->addComponent(std::move(centerLayout), engine::ui::LayoutAnchor::Center);
    auto frame = engine::ui::Frame(std::move(rootLayout));
    m_uiSystem->push(std::move(frame));
}

void BaseMenuState::update(std::chrono::nanoseconds /* timeStep */)
{
}

void BaseMenuState::render(engine::IRenderer& renderer)
{
    m_uiSystem->draw(renderer, common::Vector2D<int>(m_screenSize));
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

void BaseMenuState::openHelpMenu()
{
    auto help = std::make_unique<engine::ui::LayoutPanel>(
        engine::ui::ComponentSize(engine::ui::ComponentSizeType::Fit,
            engine::ui::ComponentSizeType::Stretch,
            common::Vector2D<double>(1, 1)),
        engine::ui::FlowDirection::Horizontal);

    auto componentSize = engine::ui::ComponentSize(
        engine::ui::ComponentSizeType::Fit,
        engine::ui::ComponentSizeType::Fit,
        common::Vector2D<double>(1, 1));

    auto center = std::make_unique<engine::ui::LayoutPanel>(
        componentSize,
        engine::ui::FlowDirection::Vertical);

    auto stack = std::make_unique<engine::ui::StackPanel>(
        componentSize,
        engine::ui::FlowDirection::Vertical);

    stack->addComponent(std::make_unique<engine::ui::Label>(
        componentSize,
        "WELCOME TO PUSH'D OUT!", 14));

    stack->addComponent(std::make_unique<engine::ui::Label>(
        componentSize,
        "THE GOAL OF THE GAME IS TO PUSH THE ENEMY (OR FRIEND) OUT OF THE STAGE AND BECOME THE MASTER OF PHYSICS."));

    stack->addComponent(std::make_unique<engine::ui::Label>(
        componentSize,
        "YOU'LL START THE MATCH WITHOUT EQUIPMENT, SO STAY CLOSE TO THE SPAWNING AREAS IN THE MAP"));

    stack->addComponent(std::make_unique<engine::ui::Label>(
        componentSize,
        "FOR A NEW JUICY WEAPON OR ITEM TO BE TESTED ON YOUR FELLOW PLAYERS."));

    auto image = std::make_unique<engine::ui::Image>(componentSize, "assets/sprites/controller.jpg");
    stack->addComponent(std::move(image));

    auto button = std::make_unique<engine::ui::Button>(componentSize, "BACK");
    button->setAction(std::make_unique<engine::ui::CustomAction>([&]() {
        m_uiSystem->pop();
    }));

    stack->addComponent(std::move(button));

    center->addComponent(std::move(stack), engine::ui::LayoutAnchor::Center);
    help->addComponent(std::move(center), engine::ui::LayoutAnchor::Center);

    auto frame = engine::ui::Frame(std::move(help));
    m_uiSystem->push(std::move(frame));
}
}
