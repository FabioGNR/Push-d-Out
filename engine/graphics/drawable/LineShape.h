#pragma once

#include <engine/common/Vector2D.h>
#include <engine/graphics/Color.h>
#include <engine/graphics/IGraphicsElement.h>

namespace engine {
class LineShape : public IGraphicsElement {
    common::Vector2D<int> m_position1;
    common::Vector2D<int> m_position2;
    const Color& m_color;

public:
    LineShape(common::Vector2D<int> pos1, common::Vector2D<int> pos2, const Color& color);
    ~LineShape() override = default;

    void draw(const IRenderer& renderer) const override;
    void accept(const IRenderVisitor& visitor) const override;

    const common::Vector2D<int>& position() const override;
    void setPosition(const common::Vector2D<int>& position) override;

    const common::Vector2D<int>& position1() const;
    const common::Vector2D<int>& position2() const;
    const Color& color() const;
};
} // end namespace engine