#pragma once

#include <engine/common/Vector2D.h>
#include <engine/graphics/IGraphicsElement.h>
#include <string>

namespace engine {
class Sprite : public IGraphicsElement {
    std::string m_spritePath;
    common::Vector2D<int> m_position;
    // TODO: Re-evaluate width and height. Just inherit from texture image?
    common::Vector2D<int> m_size;
    double m_scale;

public:
    Sprite(std::string spritePath, common::Vector2D<int> position, common::Vector2D<int> size, double scale);

    void accept(IRenderVisitor& visitor) const override;
    const std::string& spritePath() const;

    common::Vector2D<int> position() const;
    common::Vector2D<int> size() const;

    void setPosition(common::Vector2D<int> position);
    void setSize(common::Vector2D<int> size);

    double scale() const;

    bool operator==(const Sprite& rhs) const;

    bool operator!=(const Sprite& rhs) const;
};
} // end namespace engine