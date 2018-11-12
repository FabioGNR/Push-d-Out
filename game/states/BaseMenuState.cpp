#include "BaseMenuState.h"
#include "GameState.h"
#include "game/Game.h"
#include <engine/common/Vector2D.h>
#include <engine/game/IGame.h>
#include <engine/game/State.h>
#include <engine/ui/components/Component.h>
#include <engine/ui/components/CustomAction.h>
#include <engine/ui/components/Label.h>
#include <engine/ui/components/LayoutPanel.h>
#include <engine/ui/components/StackPanel.h>

using namespace std::chrono_literals;

namespace game {
BaseMenuState::BaseMenuState(engine::input::InputManager& inputManager)
    : m_uiSystem(std::make_unique<engine::ui::UISystem>(inputManager))
{
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

    m_buttonStack = std::make_shared<engine::ui::StackPanel>(
        engine::ui::ComponentSize(
            engine::ui::ComponentSizeType::Fit,
            engine::ui::ComponentSizeType::Fit,
            common::Vector2D<double>(1, 1)),
        engine::ui::FlowDirection::Vertical);
    centerLayout->addComponent(m_buttonStack, engine::ui::LayoutAnchor::Center);

    auto frame = engine::ui::Frame(rootLayout);
    m_uiSystem->push(frame);
}

void BaseMenuState::init()
{

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

void BaseMenuState::appendComponent(std::shared_ptr<engine::ui::Component> component)
{
    m_buttonStack->addComponent(component);
}

void BaseMenuState::prependComponent(std::shared_ptr<engine::ui::Component> component)
{
    m_buttonStack->addComponentFront(component);
}
} // end namespace game
