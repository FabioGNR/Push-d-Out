#include "TileSet.h"

namespace game::level::editor::ui {
void TileSet::addTileTexture(std::string textureName)
{
    m_tileTextures.push_back(std::move(textureName));
}

const std::string& TileSet::getCurrentTileTexture() const
{
    return m_tileTextures[m_currentPosition];
}

const std::string& TileSet::getNextTileTexture() const
{
    m_currentPosition++;
    if (m_currentPosition >= static_cast<int>(m_tileTextures.size())) {
        m_currentPosition = 0;
    }
    return m_tileTextures[m_currentPosition];
}

const std::string& TileSet::getPreviousTileTexture() const
{
    m_currentPosition--;
    if (m_currentPosition < 0) {
        m_currentPosition = static_cast<int>(m_tileTextures.size() - 1);
    }
    return m_tileTextures[m_currentPosition];
}

std::vector<std::string> TileSet::getRangeFromCurrent(int range) const
{
    std::vector<std::string> wrappedTextures;
    wrappedTextures.reserve(range);

    for (int i = 0; i < range; ++i) {
        const auto wrappedPosition = ((m_currentPosition - range / 2 + i) % (m_tileTextures.size()));
        const auto& texture = m_tileTextures[wrappedPosition];
        wrappedTextures.push_back(texture);
    }
    return wrappedTextures;
}
} // end namespace
