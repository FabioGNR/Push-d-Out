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
    std::vector<const IGraphicsElement*> m_shapes;

public:
    Surface(common::Vector2D<int> position, common::Vector2D<int> size, int alpha)
        : m_position{ position }
        , m_size{ size }
        , m_alpha{ alpha } {};

    void accept(IRenderVisitor& visitor) const override;

    common::Vector2D<int> position() const;
    common::Vector2D<int> size() const;
    int alpha() const;
    std::vector<const IGraphicsElement*> shapes() const;

    void draw(const IGraphicsElement*);
    void alpha(int);

    bool operator==(const Surface& rhs) const;

    bool operator!=(const Surface& rhs) const;
};
} // end namespace engine