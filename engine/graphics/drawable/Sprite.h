#pragma once

#include <engine/common/Vector2D.h>
#include <engine/graphics/IGraphicsElement.h>
#include <string>

namespace engine {
class Sprite : public IGraphicsElement {
    std::string m_spritePath;
    common::Vector2D<int> m_sourcePosition;
    common::Vector2D<int> m_position;
    common::Vector2D<int> m_sourceSize;
    common::Vector2D<double> m_scale;
    common::Vector2D<int> m_size;

public:
    Sprite(std::string spritePath, common::Vector2D<int> position, common::Vector2D<int> sourceSize, common::Vector2D<int> sourcePosition, common::Vector2D<double> scale);

    void accept(IRenderVisitor& visitor) const override;
    const std::string& spritePath() const;

    common::Vector2D<int> position() const;
    common::Vector2D<int> sourcePosition() const;
    common::Vector2D<int> sourceSize() const;
    common::Vector2D<double> scale() const;
    common::Vector2D<int> size() const;

    void setPosition(common::Vector2D<int> position);
    void setSize(common::Vector2D<int> size);

    bool operator==(const Sprite& rhs) const;

    bool operator!=(const Sprite& rhs) const;
};
} // end namespace engine