#pragma once

#include <graphics/IGraphicsElement.h>
#include <string>

namespace engine {
class Sprite : public IGraphicsElement {
    std::string m_spritePath;
    int m_x, m_y;
    // TODO: Re-evaluate width and height. Just inherit from texture image?
    int m_width, m_height;
    double m_scale;

public:
    Sprite(const std::string& spritePath, int x, int y, int width, int height, double scale);

    void accept(IRenderVisitor& visitor) const override;
    const std::string& spritePath() const;

    int x() const;
    int y() const;
    int width() const;
    int height() const;
    double scale() const;
};
} // end namespace engine