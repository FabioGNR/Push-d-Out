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
    const common::Vector2D<int> tileSize(game.getScreenSize().x / 40, game.getScreenSize().y / 24);

    m_editor.init(numTiles, tileSize);
    m_editor.setBackground("assets/sprites/sky_backdrop.jpg");
    m_inputSubscription = m_inputManager.subscribeAll([&](engine::input::maps::InputMap inputMap, auto&) {
        // Check EXIT condition
        if (inputMap.hasState(engine::input::Keys::ESCAPE, engine::input::States::PRESSED)) {
            m_context.previous();
        }

        // Tile Movement
        if (inputMap.hasState(engine::input::Keys::A, engine::input::States::PRESSED)) {
            m_editor.move(-1, 0);
        } else if (inputMap.hasState(engine::input::Keys::W, engine::input::States::PRESSED)) {
            m_editor.move(0, 1);
        } else if (inputMap.hasState(engine::input::Keys::S, engine::input::States::PRESSED)) {
            m_editor.move(0, -1);
        } else if (inputMap.hasState(engine::input::Keys::D, engine::input::States::PRESSED)) {
            m_editor.move(1, 0);
        }

        // Tile Type selection
        if (inputMap.hasState(engine::input::Keys::K, engine::input::States::PRESSED)) {
            m_editor.previousTileType();
        } else if (inputMap.hasState(engine::input::Keys::L, engine::input::States::PRESSED)) {
            m_editor.nextTileType();
        }

        // Platform Tile Sprite selection
        if (inputMap.hasState(engine::input::Keys::O, engine::input::States::PRESSED)) {
            m_editor.previousTileSprite();
        } else if (inputMap.hasState(engine::input::Keys::P, engine::input::States::PRESSED)) {
            m_editor.nextTileSprite();
        }

        // Select tile
        if (inputMap.hasState(engine::input::Keys::SPACE, engine::input::States::PRESSED)) {
            m_editor.makeSelection();
        }

        if (inputMap.hasState(engine::input::Keys::M, engine::input::States::PRESSED)) {
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
