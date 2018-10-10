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
        : m_position{ common::Vector2D(x, y) }
        , m_dimensions{ common::Vector2D(width, height) }
        , m_world{ world }
    {
    }

    double Body::getAngle() const
    {
        return m_angle;
    }

    const common::Vector2D Body::getPosition() const
    {
        return common::Vector2D(m_position.x, -(m_position.y) + m_world.getSize().y - 1);
    }

    const common::Vector2D Body::getDimensions() const
    {
        return common::Vector2D(m_dimensions.x, m_dimensions.y);
    }

    const common::Vector2D Body::getCenterPoint() const
    {
        return common::Vector2D((m_dimensions.x) / 2.0, (m_dimensions.y) / 2.0);
    }
}
}
