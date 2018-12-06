#pragma once

#include <engine/common/Vector2D.h>
#include <engine/graphics/IGraphicsElement.h>
#include <string>

namespace engine {
class Sprite : public IGraphicsElement {
public:
    std::string m_spritePath;

    common::Vector2D<int> m_position;
    common::Vector2D<int> m_size;

    common::Vector2D<int> m_sourcePosition;
    common::Vector2D<int> m_sourceSize;

public:
    Sprite(std::string spritePath, common::Vector2D<int> position, common::Vector2D<int> sourceSize, common::Vector2D<int> sourcePosition);
    Sprite(std::string spritePath, common::Vector2D<int> position, common::Vector2D<int> size);

    void draw(const IRenderer& renderer) const override;
    void accept(const IRenderVisitor& visitor) const override;

    const std::string& spritePath() const;
    const common::Vector2D<int>& position() const override;
    const common::Vector2D<int>& size() const;
    const common::Vector2D<int>& sourcePosition() const;
    const common::Vector2D<int>& sourceSize() const;

    void setPosition(const common::Vector2D<int>& position) override;
    void setSize(const common::Vector2D<int>& size);
    void setSpritePath(std::string spritePath);

    bool operator==(const Sprite& rhs) const;
    bool operator!=(const Sprite& rhs) const;
};
} // end namespace engine