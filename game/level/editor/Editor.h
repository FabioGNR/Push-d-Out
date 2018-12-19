#pragma once

#include <engine/common/Vector2D.h>

#include "game/level/Theme.h"
#include "game/level/editor/ui/Cursor.h"
#include "game/level/editor/ui/ITile.h"
#include "game/level/editor/ui/KeyboardScreen.h"
#include "game/level/editor/ui/TileSet.h"
#include "game/level/editor/ui/TileSpriteSelectionScrollbar.h"

#include <memory>
#include <unordered_map>
#include <utility>
#include <vector>

namespace engine {
class IRenderer;
}

namespace game::level {
class Editor {

    editor::ui::TileSet m_platformTileSet;
    editor::ui::TileSet m_propTileSet;

    game::level::Theme m_theme;

    std::vector<std::unique_ptr<editor::ui::ITile>> m_tiles;
    std::vector<std::unique_ptr<editor::ui::ITile>> m_props;

    common::Vector2D<int> m_tileMatrixSize;
    common::Vector2D<int> m_tileSize;

    common::Vector2D<int> m_currentTile;

    editor::ui::Cursor m_cursor;
    editor::ui::TileSpriteSelectionScrollbar m_tileSelection;

    std::vector<std::unique_ptr<editor::ui::ITile>> m_tileCursors;
    int m_selectedTileCursor{};

    std::unique_ptr<engine::Sprite> m_backgroundSprite;

    bool m_showKeyboard = false;
    std::unique_ptr<editor::ui::KeyboardScreen> m_keyboardScreen;

    // ??? need custom hasher to store Vector2D in a map
    struct VectorKeyHasher {
        size_t operator()(const common::Vector2D<int>& key) const
        {
            return std::hash<int>()(key.x) ^ std::hash<int>()(key.y);
        }
    };
    // hack to map Sprite back to Spritesheet
    std::unordered_map<common::Vector2D<int>, std::string, VectorKeyHasher> m_spritePositionToName;
    std::unordered_map<common::Vector2D<int>, std::string, VectorKeyHasher> m_propPositionToName;

public:
    Editor();

    void init(const game::level::Theme& theme, const common::Vector2D<int>& tileMatrixSize, const common::Vector2D<int>& tileSize);
    void draw(engine::IRenderer& renderer);

    int index(int x, int y) const;
    editor::ui::ITile& getTile(int x, int y);
    editor::ui::ITile& getCurrentTile();
    editor::ui::ITile& getProp(int x, int y);
    editor::ui::ITile& getCurrentProp();

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

    bool isActive = true;

private:
    void initializeTileSet();
    void initializePropSet();
    void updateSelectionScrollbar();
};
}
