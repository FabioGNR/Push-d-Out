#pragma once

#include <string>
#include <vector>

namespace game::level::editor::ui {
class TileSet {
    mutable int m_currentPosition = 0;
    std::vector<std::string> m_tileTextures{};

public:
    void addTileTexture(std::string textureName);

    const std::string& getCurrentTileTexture() const;
    const std::string& getNextTileTexture() const;
    const std::string& getPreviousTileTexture() const;
    std::vector<std::string> getRangeFromCurrent(int range) const;
};
}
