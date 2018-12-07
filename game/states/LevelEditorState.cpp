#include "LevelEditorState.h"
#include "LevelEditorMenuState.h"

#include <game/Game.h>

namespace game {
LevelEditorState::LevelEditorState(engine::IGame& context)
    : State(context)
    , m_inputManager(dynamic_cast<Game&>(context).getInputManager())
{
}

void LevelEditorState::init()
{
    const auto& game = dynamic_cast<Game&>(m_context);
    const common::Vector2D<int> numTiles(40, 24);
    const common::Vector2D<int> tileSize(game.getScreenSize().x / numTiles.x, game.getScreenSize().y / numTiles.y);

    m_editor.init(numTiles, tileSize);
    m_editor.setBackground("assets/sprites/sky_backdrop.jpg");
    m_inputSubscription = m_inputManager.subscribeAll([&](engine::input::maps::InputMap inputMap, auto&) {
        auto pressedState = engine::input::States::PRESSED;

        // Check EXIT condition
        if (inputMap.hasState(engine::input::Keys::ESCAPE, engine::input::States::PRESSED)
            || inputMap.hasState(engine::input::Keys::CON_START, engine::input::States::PRESSED)) {
            m_context.previous();
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

void LevelEditorState::update(std::chrono::nanoseconds timeStep)
{
    (void)timeStep;
}

void LevelEditorState::render(engine::IRenderer& renderer)
{
    m_editor.draw(renderer);
}
} // end namespace
