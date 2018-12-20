#include "LevelSelectorState.h"
#include "BaseMenuState.h"
#include "GameState.h"

#include <game/Game.h>

#include <engine/ui/components/Button.h>
#include <engine/ui/components/CustomAction.h>
#include <engine/ui/components/Label.h>
#include <engine/ui/components/LayoutPanel.h>
#include <engine/ui/components/StackPanel.h>

#include <boost/filesystem.hpp>
#include <game/level/reader/LevelReader.h>
#include <game/ui/MenuButton.h>

namespace game {

LevelSelectorState::LevelSelectorState(engine::IGame& context)
    : State(context)
    , m_background("", { 0, 0 }, { 0, 0 })
    , m_backgroundOverlay("assets/sprites/ui/radial_overlay.png", { 0, 0 }, { 0, 0 })
{
    auto& game = dynamic_cast<Game&>(m_context);
    m_screenSize = game.getScreenSize();
    m_uiSystem = std::make_unique<engine::ui::UISystem>(game.getInputManager());
    m_backgroundOverlay.setSize(m_screenSize);
    m_background.setSize(m_screenSize);
}

void LevelSelectorState::update(std::chrono::nanoseconds /* timeStep */)
{
}

void LevelSelectorState::render(engine::IRenderer& renderer)
{
    if (!m_background.spritePath().empty()) {
        renderer.draw(m_background);
        renderer.draw(m_backgroundOverlay);
    }
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
    auto nameLabel = std::make_unique<engine::ui::Label>(fitSize, "Select a level", 12, engine::Color{ 255, 255, 255 });
    buttonStack->addComponent(std::move(nameLabel));

    namespace fs = boost::filesystem;
    const auto path = fs::path("assets/levels");
    for (auto start = fs::directory_iterator(path); start != fs::directory_iterator(); ++start) {
        const auto file = *start;
        if (file.path().extension() != ".json") {
            break;
        }
        const std::string fileName = file.path().stem().string();
        const auto filePath = "assets/levels/" + fileName + ".json";

        buttonStack->addComponent(makeButton(fileName,
            [&, filePath]() {
                level::LevelReader reader;
                auto level = reader.build(reader.parse(filePath));

                const auto to_lower = [](std::string str) -> std::string {
                    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
                    return str;
                };
                m_background.setSpritePath("assets/sprites/themes/" + to_lower(level.theme.name) + "/background.png");
            },
            [&, filePath]() {
                try {
                    m_context.next(std::make_unique<GameState>(filePath, m_context));
                } catch (std::exception& e) {
                    m_context.previous();
                }
            }));
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

std::unique_ptr<engine::ui::Button>
LevelSelectorState::makeButton(const std::string& text, std::function<void()> onHover, std::function<void()> function)
{
    auto button = std::make_unique<game::ui::MenuButton>(
        engine::ui::ComponentSize(
            engine::ui::ComponentSizeType::Stretch,
            engine::ui::ComponentSizeType::Fit,
            common::Vector2D<double>(0.2, 1)),
        text,
        std::move(onHover));
    button->setAction(std::make_unique<engine::ui::CustomAction>(std::move(function)));
    return std::move(button);
}
}
