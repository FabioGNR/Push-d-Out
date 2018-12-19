#include "BaseMenuState.h"
#include "GameState.h"
#include "OptionMenuState.h"
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
#include <game/ui/MenuButton.h>

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
            engine::ui::ComponentSizeType::Stretch,
            engine::ui::ComponentSizeType::Stretch,
            common::Vector2D<double>(1, 1)),
        engine::ui::FlowDirection::Vertical);

    auto content = std::make_unique<engine::ui::StackPanel>(
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

    auto titleSize = engine::ui::ComponentSize(
        engine::ui::ComponentSizeType::Fit,
        engine::ui::ComponentSizeType::Fit,
        common::Vector2D<double>(1, 1));
    titleSize.setMarginStart({ 0, 25 });
    titleSize.setMarginEnd({ 0, 50 });
    auto title = std::make_unique<engine::ui::Label>(titleSize, "Push'd Out!", 48);

    buttonStack->addComponent(std::move(title));
    prependButtons(*buttonStack);

    buttonStack->addComponent(makeStretchedButton("OPTIONS", [&]() {
        m_context.next(std::make_unique<OptionMenuState>(m_context));
    }));

    buttonStack->addComponent(makeStretchedButton("HELP", [&]() {
        openHelpMenu();
    }));

    appendButtons(*buttonStack);
    buttonStack->addComponent(makeStretchedButton("QUIT", [&]() {
        m_context.stop();
    }));

    auto bannerLayout = std::make_unique<engine::ui::LayoutPanel>(
        engine::ui::ComponentSize(
            engine::ui::ComponentSizeType::Fit,
            engine::ui::ComponentSizeType::Fit,
            common::Vector2D<double>(1, 1)),
        engine::ui::FlowDirection::Horizontal);

    auto banner = std::make_unique<engine::ui::Image>(
        engine::ui::ComponentSize(
            engine::ui::ComponentSizeType::Relative,
            engine::ui::ComponentSizeType::Relative,
            common::Vector2D<double>(0.2, 0.2)),
        "assets/sprites/advertisement.png");
    bannerLayout->addComponent(std::move(banner), engine::ui::LayoutAnchor::Center);

    auto buttonLayout = std::make_unique<engine::ui::LayoutPanel>(
        engine::ui::ComponentSize(
            engine::ui::ComponentSizeType::Fit,
            engine::ui::ComponentSizeType::Fit,
            common::Vector2D<double>(1, 1)),
        engine::ui::FlowDirection::Horizontal);

    buttonLayout->addComponent(std::move(buttonStack), engine::ui::LayoutAnchor::Center);
    content->addComponent(std::move(buttonLayout));

    rootLayout->addComponent(std::move(content), engine::ui::LayoutAnchor::Start);
    rootLayout->addComponent(std::move(bannerLayout), engine::ui::LayoutAnchor::End);
    auto frame = engine::ui::Frame(std::move(rootLayout));
    m_uiSystem->push(std::move(frame));
}

void BaseMenuState::update(std::chrono::nanoseconds /* timeStep */)
{
}

void BaseMenuState::render(engine::IRenderer& renderer)
{
    if (m_background != nullptr) {
        renderer.draw(*m_background);
    }
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
    engine::Sprite sprite{ "assets/sprites/ui/bg.png", { 0, 0 }, { 0, 0 } };
    m_background = std::make_unique<engine::Sprite>(sprite);
    m_background->setSize(m_screenSize);

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

    stack->addComponent(std::make_unique<engine::ui::Image>(componentSize, "assets/sprites/controller.png"));

    stack->addComponent(makeFittedButton("BACK", [&]() {
        m_background = nullptr;
        m_uiSystem->pop();
    }));

    center->addComponent(std::move(stack), engine::ui::LayoutAnchor::Center);
    help->addComponent(std::move(center), engine::ui::LayoutAnchor::Center);

    auto frame = engine::ui::Frame(std::move(help));
    m_uiSystem->push(std::move(frame));
}

std::unique_ptr<engine::ui::Button> BaseMenuState::makeStretchedButton(const std::string& text,
    std::function<void()> function)
{
    auto button = std::make_unique<game::ui::MenuButton>(
        engine::ui::ComponentSize(
            engine::ui::ComponentSizeType::Stretch,
            engine::ui::ComponentSizeType::Fit,
            common::Vector2D<double>(0.2, 1)),
        text);
    button->setAction(std::make_unique<engine::ui::CustomAction>(std::move(function)));
    return std::move(button);
}

std::unique_ptr<engine::ui::Button>
BaseMenuState::makeFittedButton(const std::string& text, std::function<void()> function)
{
    auto button = std::make_unique<game::ui::MenuButton>(
        engine::ui::ComponentSize(
            engine::ui::ComponentSizeType::Fit,
            engine::ui::ComponentSizeType::Fit,
            common::Vector2D<double>(1, 1)),
        text);
    button->setAction(std::make_unique<engine::ui::CustomAction>(std::move(function)));
    return std::move(button);
}
}
