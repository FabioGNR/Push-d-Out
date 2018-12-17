#pragma once

#include <engine/graphics/drawable/Sprite.h>
#include <memory>
#include <string>
#include <vector>

namespace game::level::editor::ui {
class TileSet {
    mutable int m_currentPosition = 0;
    std::vector<std::unique_ptr<engine::Sprite>> m_tileTextures{};

public:
    void addTileTexture(std::unique_ptr<engine::Sprite> sprite);

    const engine::Sprite* getCurrentTileTexture() const;
    const engine::Sprite* getNextTileTexture() const;
    const engine::Sprite* getPreviousTileTexture() const;
    std::vector<const engine::Sprite*> getRangeFromCurrent(int range) const;

    void clear()
    {
        m_currentPosition = 0;
        m_tileTextures.clear();
    }
};
}
