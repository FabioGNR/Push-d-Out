#include "TileSet.h"

#include <algorithm>

namespace game::level::editor::ui {
void TileSet::addTileTexture(std::unique_ptr<engine::Sprite> sprite)
{
    m_tileTextures.push_back(std::move(sprite));
}

const engine::Sprite* TileSet::getCurrentTileTexture() const
{
    return m_tileTextures[m_currentPosition].get();
}

const engine::Sprite* TileSet::getNextTileTexture() const
{
    m_currentPosition++;
    if (m_currentPosition >= static_cast<int>(m_tileTextures.size())) {
        m_currentPosition = 0;
    }
    return m_tileTextures[m_currentPosition].get();
}

const engine::Sprite* TileSet::getPreviousTileTexture() const
{
    m_currentPosition--;
    if (m_currentPosition < 0) {
        m_currentPosition = static_cast<int>(m_tileTextures.size() - 1);
    }
    return m_tileTextures[m_currentPosition].get();
}

std::vector<const engine::Sprite*> TileSet::getRangeFromCurrent(int range) const
{
    std::vector<const engine::Sprite*> wrappedTextures;
    wrappedTextures.reserve(range);

    const int halvedRange = range / 2;

    // https://stackoverflow.com/questions/43827464/wrap-negative-index-to-size-of-array
    // if index is negative, wrap it back around to the back of the vector
    const auto mod_floor = [](int a, int n) {
        return ((a % n) + n) % n;
    };

    for (int i = 0; i < range; ++i) {
        const int wrappedPosition = mod_floor(m_currentPosition - halvedRange + i, m_tileTextures.size());
        const auto& texture = m_tileTextures[wrappedPosition];
        wrappedTextures.push_back(texture.get());
    }
    return wrappedTextures;
}
} // end namespace
