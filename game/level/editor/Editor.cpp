#include "Editor.h"

#include <game/level/LevelDomain.h>
#include <game/level/editor/ui/PlatformTile.h>
#include <game/level/editor/ui/SpawnTile.h>

#include <engine/graphics/IRenderer.h>

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
    , m_tileSelection(m_tileSet, { 0, 0 }, { 0, 0 })
    , m_backgroundSprite(nullptr)
    , m_keyboardScreen(nullptr)
{
    //TODO: Not hardcode this

    //constexpr std::array<const char* numbers = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
    const std::string numbers = "0123456789";

    // add empty tile for nothing
    m_tileSet.addTileTexture("");
    for (int i = 0; i <= 230; ++i) {
        // https://stackoverflow.com/questions/49929474/how-to-insert-an-integer-with-leading-zeros-into-a-stdstring
        std::string str{ "assets/sprites/blocks/isometric_pixel_flat_####.png" };
        int num = i;

        std::transform(str.rbegin(), str.rend(), str.rbegin(),
            [&](auto ch) {
                if ('#' == ch) {
                    ch = numbers.at(num % 10); // or '0' + num % 10;
                    num /= 10;
                }
                return ch;
            });

        m_tileSet.addTileTexture(str);
    }
}

void Editor::init(const common::Vector2D<int>& tileMatrixSize, const common::Vector2D<int>& tileSize)
{
    m_tileMatrixSize = tileMatrixSize;
    m_tileSize = tileSize;
    m_tileSelection.setSize({ 200, 100 });

    m_keyboardScreen = std::make_unique<ui::KeyboardScreen>(m_tileMatrixSize * m_tileSize);

    m_tiles.clear();
    m_tiles.reserve(m_tileMatrixSize.x * m_tileMatrixSize.y);

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

    if (getCurrentTile().getTileType() == TileType::PLATFORM) {
        m_tileSelection.draw(renderer);
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
    updateSelectionScrollbar();
}

ui::ITile& Editor::getCurrentTile()
{
    return *m_tiles[index(m_currentTile.x, m_currentTile.y)];
}

void Editor::nextTileSprite()
{
    (void)m_tileSet.getNextTileTexture();
}

void Editor::previousTileSprite()
{
    (void)m_tileSet.getPreviousTileTexture();
}

void Editor::updateSelectionScrollbar()
{
    // if current tile is too close to the left side
    // and the selectionBox does not fit on the left
    // move it to the right
    if (getCurrentTile().position().x < m_tileSelection.getSize().x) {
        m_tileSelection.setPosition(getCurrentTile().position() + common::Vector2D<int>{ m_tileSize.x, 0 });
    } else {
        m_tileSelection.setPosition(getCurrentTile().position() - common::Vector2D<int>{ m_tileSelection.getSize().x, 0 });
    }
}

void Editor::nextTileType()
{
    if (getCurrentTile().getTileType() == TileType::PLATFORM) {
        m_tiles[index(m_currentTile.x, m_currentTile.y)] = std::make_unique<ui::SpawnTile>(getCurrentTile().position(), m_tileSize);
    } else {
        m_tiles[index(m_currentTile.x, m_currentTile.y)] = std::make_unique<ui::PlatformTile>(getCurrentTile().position(), m_tileSize);
    }
}

void Editor::previousTileType()
{
    if (getCurrentTile().getTileType() == TileType::PLATFORM) {
        m_tiles[index(m_currentTile.x, m_currentTile.y)] = std::make_unique<ui::SpawnTile>(getCurrentTile().position(), m_tileSize);
    } else {
        m_tiles[index(m_currentTile.x, m_currentTile.y)] = std::make_unique<ui::PlatformTile>(getCurrentTile().position(), m_tileSize);
    }
}

void Editor::makeSelection()
{
    if (m_showKeyboard) {
        m_keyboardScreen->makeSelection();
        return;
    }
    // toggle selection
    getCurrentTile().select(!getCurrentTile().isSelected());

    if (getCurrentTile().getTileType() == TileType::PLATFORM) {
        auto* currentTile = dynamic_cast<ui::PlatformTile*>(&getCurrentTile());
        currentTile->setTileSprite(m_tileSet.getCurrentTileTexture());
    }
}

void Editor::exportAsJson(const std::string& fileName)
{
    Level level;
    level.name = fileName;
    level.theme = []() {
        Theme theme;
        theme.name = "Earth";
        return theme;
    }();
    level.width = m_tileMatrixSize.x;
    level.height = m_tileMatrixSize.y;

    for (int y = 0; y < m_tileMatrixSize.y; ++y) {
        for (int x = 0; x < m_tileMatrixSize.x; ++x) {
            const auto* tile = &getTile(x, y);
            if (getTile(x, y).getTileType() == TileType::PLATFORM) {
                const auto* platformTile = dynamic_cast<const ui::PlatformTile*>(tile);
                if (platformTile->getTileSprite() != nullptr) {
                    level.tiles.push_back(Tile{
                        static_cast<double>(x),
                        static_cast<double>(m_tileMatrixSize.y - y),
                        "middleMiddle",
                        //platformTile->getTileSprite()->setSpritePath(),
                        PlatformKind::Solid });
                }
            } else {
                level.CharacterSpawns.push_back(SpawnPoint{
                    static_cast<double>(x),
                    static_cast<double>(m_tileMatrixSize.y - y) });
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

void Editor::setBackground(const std::string& backgroundPath)
{
    m_backgroundSprite = std::make_unique<engine::Sprite>(backgroundPath, common::Vector2D<int>{ 0, 0 }, m_tileSize * m_tileMatrixSize);
}

} // end namespace
