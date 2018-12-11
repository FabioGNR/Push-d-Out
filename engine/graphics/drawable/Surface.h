#pragma once

#include "engine/common/Vector2D.h"
#include "engine/graphics/Color.h"
#include "engine/graphics/IGraphicsElement.h"
#include <memory>
#include <vector>

namespace engine {
class Surface : public IGraphicsElement {
    common::Vector2D<int> m_position;
    common::Vector2D<int> m_size;
    int m_alpha;
    std::vector<std::unique_ptr<IGraphicsElement>> m_shapes;

public:
    Surface(const common::Vector2D<int>& position, const common::Vector2D<int>& size, int alpha)
        : m_position{ position }
        , m_size{ size }
        , m_alpha{ alpha } {};

    void draw(const IRenderer& renderer) const override;
    void accept(const IRenderVisitor& visitor) const override;

    const common::Vector2D<int>& position() const override;
    const common::Vector2D<int>& size() const;

    void setPosition(const common::Vector2D<int>& position) override;
    void setSize(const common::Vector2D<int>& size);

    int alpha() const;

    void addShape(std::unique_ptr<IGraphicsElement> shape);
    void setAlpha(int alpha);

    void clear()
    {
        m_shapes.clear();
    }

    bool operator==(const Surface& rhs) const;

    bool operator!=(const Surface& rhs) const;
};
} // end namespace engine