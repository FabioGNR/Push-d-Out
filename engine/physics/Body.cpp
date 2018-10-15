#include "Body.h"
#include "World.h"
#include <Box2D/Box2D.h>
#include <memory>

namespace engine {
namespace physics {
    /**
         * Creates a new body with the size of <code>width * unitSize</code>
         * @param x     position in units of the body
         * @param y     position in units of the body
         * @param width     width in units of the body
         * @param height    height in units of the body
         * @param unitSize  size of 1 unit
         * @param world     Box2D's world object
         */
    Body::Body(double x, double y, double width, double height, World& world)
        : m_position{ common::Vector2D<int>(x, y) }
        , m_dimensions{ common::Vector2D<int>(width, height) }
        , m_world{ world }
    {
    }

    double Body::getAngle() const
    {
        return m_angle;
    }

    const common::Vector2D<int> Body::getPosition() const
    {
        return common::Vector2D<int>(m_position.x, -(m_position.y) + m_world.getSize().y - 1);
    }

    const common::Vector2D<int> Body::getDimensions() const
    {
        return m_dimensions;
    }

    const common::Vector2D<int> Body::getCenterPoint() const
    {
        return common::Vector2D<int>((m_dimensions.x) / 2.0, (m_dimensions.y) / 2.0);
    }
}
}
