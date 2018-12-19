#include "Editor.h"

#include <game/builders/SpriteBuilder.h>
#include <game/level/LevelDomain.h>
#include <game/level/editor/ui/PlatformTile.h>
#include <game/level/editor/ui/SpawnTile.h>

#include <engine/graphics/IRenderer.h>

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <memory>

namespace game::level {

using namespace editor;

Editor::Editor()
    : m_tileMatrixSize(0, 0)
    , m_tileSize(0, 0)
    , m_currentTile(0, 0)
    , m_cursor("assets/sprites/cursor.png")
    , m_tileSelection(&m_platformTileSet, { 0, 0 }, { 0, 0 })
    , m_backgroundSprite(nullptr)
    , m_keyboardScreen(nullptr)
{
}

void Editor::init(const game::level::Theme& theme, const common::Vector2D<int>& tileMatrixSize, const common::Vector2D<int>& tileSize)
{
    m_theme = theme;
    m_tileMatrixSize = tileMatrixSize;
    m_tileSize = tileSize;
    m_tileSelection.setSize({ 200, 100 });

    initializeTileSet();

    m_keyboardScreen = std::make_unique<ui::KeyboardScreen>(m_tileMatrixSize * m_tileSize);

    m_tiles.clear();
    m_tiles.reserve(m_tileMatrixSize.x * m_tileMatrixSize.y);

    m_tileCursors.clear();
    m_tileCursors.push_back(std::make_unique<ui::PlatformTile>(
        common::Vector2D<int>(0, 0),
        m_tileSize));
    m_tileCursors.push_back(std::make_unique<ui::SpawnTile>(
        ui::SpawnTile::SpawnType::CHARACTER,
        common::Vector2D<int>(0, 0),
        m_tileSize));
    m_tileCursors.push_back(std::make_unique<ui::SpawnTile>(
        ui::SpawnTile::SpawnType::EQUIPMENT,
        common::Vector2D<int>(0, 0),
        m_tileSize));

    for (int y = 0; y < m_tileMatrixSize.y; ++y) {
        for (int x = 0; x < m_tileMatrixSize.x; ++x) {
            m_tiles.push_back(std::make_unique<ui::PlatformTile>(
                common::Vector2D<int>(x * m_tileSize.x, y * m_tileSize.y),
                m_tileSize));
        }
    }

    m_keyboardScreen->onOk([&]() {
        exportAsJson(m_keyboardScreen->getInputText());
        showKeyboard(false);
    });
    m_keyboardScreen->onCancel([&]() {
        showKeyboard(false);
    });

    auto& currentTile = getCurrentTile();
    m_cursor.setPosition(currentTile.position());
    updateSelectionScrollbar();
}

void Editor::draw(engine::IRenderer& renderer)
{
    if (m_showKeyboard) {
        m_keyboardScreen->draw(renderer);
        return;
    }

    if (m_backgroundSprite != nullptr) {
        renderer.draw(*m_backgroundSprite);
    }
    for (const auto& tile : m_tiles) {
        tile->draw(renderer);
    }

    m_cursor.draw(renderer);

    if (m_tileCursors[m_selectedTileCursor]->getTileType() == TileType::PLATFORM) {
        m_tileSelection.draw(renderer);
    }

    if (m_tileCursors[m_selectedTileCursor]) {
        m_tileCursors[m_selectedTileCursor]->draw(renderer);
    }
}

int Editor::index(int x, int y) const
{
    return x + m_tileMatrixSize.x * y;
}

ui::ITile& Editor::getTile(int x, int y)
{
    return *m_tiles[index(x, y)];
}

void Editor::move(int x, int y)
{
    if (m_showKeyboard) {
        m_keyboardScreen->move(x, y);
        return;
    }

    m_currentTile.x = std::clamp(m_currentTile.x + x, 0, m_tileMatrixSize.x - 1);
    m_currentTile.y = std::clamp(m_currentTile.y - y, 0, m_tileMatrixSize.y - 1);

    m_cursor.setPosition(getCurrentTile().position());
    m_tileCursors[m_selectedTileCursor]->setPosition(getCurrentTile().position());
    updateSelectionScrollbar();
}

ui::ITile& Editor::getCurrentTile()
{
    return *m_tiles[index(m_currentTile.x, m_currentTile.y)];
}

void Editor::nextTileSprite()
{
    if (m_tileCursors[m_selectedTileCursor]->getTileType() == TileType::PLATFORM) {
        m_tileCursors[m_selectedTileCursor]->setTileSprite(m_platformTileSet.getNextTileTexture());
        move(0, 0);
    }
}

void Editor::previousTileSprite()
{
    if (m_tileCursors[m_selectedTileCursor]->getTileType() == TileType::PLATFORM) {
        m_tileCursors[m_selectedTileCursor]->setTileSprite(m_platformTileSet.getPreviousTileTexture());
        move(0, 0);
    }
}

void Editor::updateSelectionScrollbar()
{
    // if current tile is too close to the left side
    // and the selectionBox does not fit on the left
    // move it to the right
    if (m_tileCursors[m_selectedTileCursor]->position().x < m_tileSelection.getSize().x) {
        m_tileSelection.setPosition(getCurrentTile().position() + common::Vector2D<int>{ m_tileSize.x, 0 });
    } else {
        m_tileSelection.setPosition(getCurrentTile().position() - common::Vector2D<int>{ m_tileSelection.getSize().x, 0 });
    }
}

void Editor::nextTileType()
{
    m_selectedTileCursor = (m_selectedTileCursor + 1) % m_tileCursors.size();
    move(0, 0);
}

void Editor::previousTileType()
{
    m_selectedTileCursor = (m_selectedTileCursor - 1) % m_tileCursors.size();
    move(0, 0);
}

void Editor::setBackground(const std::string& backgroundPath)
{
    const common::Vector2D<int> zero{ 0, 0 };
    m_backgroundSprite = std::make_unique<engine::Sprite>(backgroundPath, zero, zero, zero);
    m_backgroundSprite->setSize(m_tileSize * m_tileMatrixSize);
}

void Editor::makeSelection()
{
    if (m_showKeyboard) {
        m_keyboardScreen->makeSelection();
        return;
    }

    if (m_tileCursors[m_selectedTileCursor]->getTileType() == TileType::SPAWN) {
        auto* tile = dynamic_cast<editor::ui::SpawnTile*>(m_tileCursors[m_selectedTileCursor].get());
        m_tiles[index(m_currentTile.x, m_currentTile.y)] = std::make_unique<editor::ui::SpawnTile>(tile->getSpawnType(),
            tile->position(), getCurrentTile().position());
        getCurrentTile().setTileSprite(m_tileCursors[m_selectedTileCursor]->getTileSprite());
    } else if (m_tileCursors[m_selectedTileCursor]->getTileType() == TileType::PLATFORM) {
        auto* tile = dynamic_cast<editor::ui::PlatformTile*>(m_tileCursors[m_selectedTileCursor].get());
        m_tiles[index(m_currentTile.x, m_currentTile.y)] = std::make_unique<editor::ui::PlatformTile>(
            tile->position(), getCurrentTile().position());
        getCurrentTile().setTileSprite(m_tileCursors[m_selectedTileCursor]->getTileSprite());
    }
}

void Editor::exportAsJson(const std::string& fileName)
{
    Level level;
    level.name = fileName;
    level.theme = m_theme;
    level.width = m_tileMatrixSize.x;
    level.height = m_tileMatrixSize.y;

    for (int y = 0; y < m_tileMatrixSize.y; ++y) {
        for (int x = 0; x < m_tileMatrixSize.x; ++x) {
            if (getTile(x, y).getTileType() == TileType::PLATFORM) {
                if (getTile(x, y).getTileSprite() != nullptr) {
                    level.tiles.push_back(Tile{
                        static_cast<double>(x),
                        static_cast<double>(m_tileMatrixSize.y - y),
                        m_spritePositionToName[getTile(x, y).getTileSprite()->sourcePosition()],
                        PlatformKind::Solid });
                }
            } else {
                const auto* spawnTile = dynamic_cast<ui::SpawnTile*>(&getTile(x, y));
                if (spawnTile->getSpawnType() == ui::SpawnTile::SpawnType::CHARACTER) {
                    level.CharacterSpawns.push_back(SpawnPoint{
                        static_cast<double>(x),
                        static_cast<double>(m_tileMatrixSize.y - y) });
                } else {
                    level.EquipmentSpawns.push_back(SpawnPoint{
                        static_cast<double>(x),
                        static_cast<double>(m_tileMatrixSize.y - y) });
                }
            }
        }
    }

    json j;
    to_json(j, level);

    std::ofstream oss("assets/levels/" + level.name + ".json");
    oss << std::setw(4) << j << std::endl;
}

void Editor::showKeyboard(bool shown)
{
    m_showKeyboard = shown;
}

void Editor::toggleKeyboard()
{
    m_showKeyboard = !m_showKeyboard;
}

void Editor::initializeTileSet()
{
    m_platformTileSet.clear();

    // add empty tile for nothing
    m_platformTileSet.addTileTexture(nullptr);

    // ;-;
    const auto to_lower = [](std::string str) -> std::string {
        std::transform(str.begin(), str.end(), str.begin(), ::tolower);
        return str;
    };

    setBackground("assets/sprites/themes/" + to_lower(m_theme.name) + "/background.png");

    game::builders::SpriteBuilder spriteBuilder("assets/sprites/themes/" + to_lower(m_theme.name) + "/" + to_lower(m_theme.name) + ".png", "assets/sprites/themes/datafile.json");
    const auto spriteMap = spriteBuilder.build();
    for (const auto& [spriteName, component] : spriteMap) {
        const auto& spriteResource = component.sprites.front();
        auto sprite = std::make_unique<engine::Sprite>(spriteResource.spriteSheet, spriteResource.offset, spriteResource.size, spriteResource.position);
        sprite->setSize(m_tileSize);
        m_platformTileSet.addTileTexture(std::move(sprite));

        m_spritePositionToName[spriteResource.position] = spriteName;
    }
}

} // end namespace
