#pragma once

#include <graphics/IGraphicsElement.h>
#include <string>
#include <common/Vector2D.h>

namespace engine {
class Sprite : public IGraphicsElement {
    std::string m_spritePath;
    common::Vector2D<int> m_position;
    // TODO: Re-evaluate width and height. Just inherit from texture image?
    common::Vector2D<int> m_size;
    double m_scale;

public:
    Sprite(const std::string& spritePath, common::Vector2D<int> position, common::Vector2D<int> size, double scale);

    void accept(IRenderVisitor& visitor) const override;
    const std::string& spritePath() const;

    common::Vector2D<int> position() const;
    common::Vector2D<int> size() const;
    double scale() const;
};
} // end namespace engine