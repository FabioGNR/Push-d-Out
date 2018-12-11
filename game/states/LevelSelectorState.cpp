#include "LevelSelectorState.h"
#include "GameState.h"

#include <game/Game.h>

#include <engine/ui/components/Button.h>
#include <engine/ui/components/CustomAction.h>
#include <engine/ui/components/Label.h>
#include <engine/ui/components/LayoutPanel.h>
#include <engine/ui/components/StackPanel.h>

#include <boost/filesystem.hpp>

namespace game {

LevelSelectorState::LevelSelectorState(engine::IGame& context)
    : State(context)
{
    auto& game = dynamic_cast<Game&>(m_context);
    m_screenSize = game.getScreenSize();
    m_uiSystem = std::make_unique<engine::ui::UISystem>(game.getInputManager());
}

void LevelSelectorState::update(std::chrono::nanoseconds /* timeStep */)
{
}

void LevelSelectorState::render(engine::IRenderer& renderer)
{
    m_uiSystem->draw(renderer, m_screenSize);
}

void LevelSelectorState::init()
{
    const auto fitSize = engine::ui::ComponentSize(
        engine::ui::ComponentSizeType::Fit,
        engine::ui::ComponentSizeType::Fit);
    auto rootLayout = std::make_unique<engine::ui::LayoutPanel>(
        engine::ui::ComponentSize(
            engine::ui::ComponentSizeType::Fit, engine::ui::ComponentSizeType::Stretch,
            common::Vector2D<double>(1, 1)),
        engine::ui::FlowDirection::Horizontal);
    auto centerLayout = std::make_unique<engine::ui::LayoutPanel>(fitSize, engine::ui::FlowDirection::Vertical);
    auto buttonStack = std::make_unique<engine::ui::StackPanel>(fitSize, engine::ui::FlowDirection::Vertical);
    auto nameLabel = std::make_unique<engine::ui::Label>(fitSize, "Select a level");
    buttonStack->addComponent(std::move(nameLabel));

    namespace fs = boost::filesystem;
    const auto path = fs::path("assets/levels");
    for (auto start = fs::directory_iterator(path); start != fs::directory_iterator(); ++start) {
        const auto file = *start;
        if (file.path().extension() != ".json") {
            break;
        }
        const std::string filePath = file.path().stem().string();
        std::unique_ptr<engine::ui::IAction> levelAction = std::make_unique<engine::ui::CustomAction>([&, filePath]() {
            try {
                m_context.next(std::make_unique<GameState>("assets/levels/" + filePath + ".json", m_context));
            } catch (std::exception& e) {
                m_context.previous();
            }
        });

        auto levelButton = std::make_unique<engine::ui::Button>(fitSize, filePath);
        levelButton->setAction(std::move(levelAction));
        buttonStack->addComponent(std::move(levelButton));
    }

    centerLayout->addComponent(std::move(buttonStack), engine::ui::LayoutAnchor::Center);
    rootLayout->addComponent(std::move(centerLayout), engine::ui::LayoutAnchor::Center);
    auto frame = engine::ui::Frame(std::move(rootLayout));
    m_uiSystem->push(std::move(frame));
}

void LevelSelectorState::resume()
{
    m_uiSystem->setActive(true);
}

void LevelSelectorState::pause()
{
    m_uiSystem->setActive(false);
}

void LevelSelectorState::close()
{
    m_uiSystem->setActive(false);
}
}
