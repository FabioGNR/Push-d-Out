#pragma once

#include <engine/common/Vector2D.h>

#include <game/level/editor/ui/Cursor.h>
#include <game/level/editor/ui/ITile.h>
#include <game/level/editor/ui/KeyboardScreen.h>
#include <game/level/editor/ui/TileSet.h>
#include <game/level/editor/ui/TileSpriteSelectionScrollbar.h>

#include <memory>
#include <vector>

namespace engine {
class IRenderer;
}

namespace game::level {
class Editor {
    editor::ui::TileSet m_tileSet;

    std::vector<std::unique_ptr<editor::ui::ITile>> m_tiles;
    common::Vector2D<int> m_tileMatrixSize;
    common::Vector2D<int> m_tileSize;

    common::Vector2D<int> m_currentTile;

    editor::ui::Cursor m_cursor;
    editor::ui::TileSpriteSelectionScrollbar m_tileSelection;

    std::unique_ptr<engine::Sprite> m_backgroundSprite;

    bool m_showKeyboard = false;
    std::unique_ptr<editor::ui::KeyboardScreen> m_keyboardScreen;

public:
    Editor();

    void init(const common::Vector2D<int>& tileMatrixSize, const common::Vector2D<int>& tileSize);
    void draw(engine::IRenderer& renderer);

    int index(int x, int y) const;
    editor::ui::ITile& getTile(int x, int y);
    editor::ui::ITile& getCurrentTile();

    void move(int x, int y);

    void nextTileType();
    void previousTileType();

    void nextTileSprite();
    void previousTileSprite();

    void toggleKeyboard();
    void showKeyboard(bool shown);

    void setBackground(const std::string& backgroundPath);

    void makeSelection();

    void exportAsJson(const std::string& fileName);

private:
    void updateSelectionScrollbar();
};
}
