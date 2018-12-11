#include "LevelEditorState.h"
#include "LevelEditorMenuState.h"

#include <game/Game.h>

#include <engine/ui/components/Button.h>
#include <engine/ui/components/CustomAction.h>
#include <engine/ui/components/IAction.h>
#include <engine/ui/components/Label.h>
#include <engine/ui/components/LayoutPanel.h>

#include <boost/filesystem.hpp>
#include <game/level/reader/ThemeReader.h>

namespace game {
LevelEditorState::LevelEditorState(engine::IGame& context)
    : State(context)
    , m_inputManager(dynamic_cast<Game&>(context).getInputManager())
{
    auto& game = dynamic_cast<Game&>(m_context);
    m_screenSize = game.getScreenSize();
    m_uiSystem = std::make_unique<engine::ui::UISystem>(game.getInputManager());
}

void LevelEditorState::init()
{
    m_uiSystem->setActive(true);
    m_showThemeSelection = true;

    const auto fitSize = engine::ui::ComponentSize(
        engine::ui::ComponentSizeType::Stretch,
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
    const auto path = fs::path("assets/themes");
    for (auto start = fs::directory_iterator(path); start != fs::directory_iterator(); ++start) {
        const auto file = *start;
        if (file.path().extension() != ".json") {
            break;
        }
        const std::string filePath = file.path().string();
        const auto fileName = file.path().stem().string();
        std::unique_ptr<engine::ui::IAction> levelAction = std::make_unique<engine::ui::CustomAction>([&, filePath]() {
            game::level::ThemeReader reader;
            auto json = reader.parse(filePath);
            auto theme = reader.build(json);
            initEditor(theme);
        });

        auto levelButton = std::make_unique<engine::ui::Button>(fitSize, fileName);
        levelButton->setAction(std::move(levelAction));
        buttonStack->addComponent(std::move(levelButton));
    }

    centerLayout->addComponent(std::move(buttonStack), engine::ui::LayoutAnchor::Center);
    rootLayout->addComponent(std::move(centerLayout), engine::ui::LayoutAnchor::Center);
    auto frame = engine::ui::Frame(std::move(rootLayout));
    m_uiSystem->push(std::move(frame));
}

void LevelEditorState::update(std::chrono::nanoseconds timeStep)
{
    (void)timeStep;
}

void LevelEditorState::render(engine::IRenderer& renderer)
{
    if (m_showThemeSelection) {
        m_uiSystem->draw(renderer, m_screenSize);
    } else {
        m_editor.draw(renderer);
    }
}

void LevelEditorState::initEditor(const game::level::Theme& theme)
{
    m_uiSystem->setActive(false);
    m_showThemeSelection = false;

    const auto& game = dynamic_cast<Game&>(m_context);
    const common::Vector2D<int> numTiles(40, 24);
    const common::Vector2D<int> tileSize(game.getScreenSize().x / numTiles.x, game.getScreenSize().y / numTiles.y);

    m_editor.init(theme, numTiles, tileSize);
    m_inputSubscription = m_inputManager->subscribeAll([&](engine::input::maps::InputMap inputMap, auto&) {
        auto pressedState = engine::input::States::PRESSED;

        // Check EXIT condition
        if (inputMap.hasState(engine::input::Keys::ESCAPE, engine::input::States::PRESSED)
            || inputMap.hasState(engine::input::Keys::CON_START, engine::input::States::PRESSED)) {
            auto menuState = std::make_unique<LevelEditorMenuState>(&m_editor, m_context);
            m_context.next(std::move(menuState));
        }

        // Tile Movement
        auto controlStickX = engine::input::AnalogKeys::CON_LEFTSTICK_X;
        auto controlStickY = engine::input::AnalogKeys::CON_LEFTSTICK_Y;

        if (inputMap.hasState(engine::input::Keys::A, pressedState)
            || (inputMap.hasState(controlStickX, pressedState) && inputMap.getValue(controlStickX) < -1)) {
            m_editor.move(-1, 0);
        } else if (inputMap.hasState(engine::input::Keys::W, pressedState)
            || (inputMap.hasState(controlStickY, pressedState) && inputMap.getValue(controlStickY) < -1)) {
            m_editor.move(0, 1);
        } else if (inputMap.hasState(engine::input::Keys::S, pressedState)
            || (inputMap.hasState(controlStickY, pressedState) && inputMap.getValue(controlStickY) > 1)) {
            m_editor.move(0, -1);
        } else if (inputMap.hasState(engine::input::Keys::D, pressedState)
            || (inputMap.hasState(controlStickX, pressedState) && inputMap.getValue(controlStickX) > 1)) {
            m_editor.move(1, 0);
        }

        // Tile Type selection
        if (inputMap.hasState(engine::input::Keys::K, pressedState)
            || inputMap.hasState(engine::input::Keys::CON_DPAD_DOWN, pressedState)) {
            m_editor.previousTileType();
        } else if (inputMap.hasState(engine::input::Keys::L, pressedState)
            || inputMap.hasState(engine::input::Keys::CON_DPAD_UP, pressedState)) {
            m_editor.nextTileType();
        }

        // Platform Tile Sprite selection
        if (inputMap.hasState(engine::input::Keys::O, pressedState)
            || inputMap.hasState(engine::input::Keys::CON_DPAD_RIGHT, pressedState)) {
            m_editor.previousTileSprite();
        } else if (inputMap.hasState(engine::input::Keys::P, pressedState)
            || inputMap.hasState(engine::input::Keys::CON_DPAD_LEFT, pressedState)) {
            m_editor.nextTileSprite();
        }

        // Select tile
        if (inputMap.hasState(engine::input::Keys::SPACE, pressedState)
            || inputMap.hasState(engine::input::Keys::CON_A, pressedState)) {
            m_editor.makeSelection();
        }

        if (inputMap.hasState(engine::input::Keys::M, pressedState)) {
            m_editor.toggleKeyboard();
        }
    });
}
} // end namespace
