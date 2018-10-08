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
    Body::Body(double x, double y, double width, double height, int unitSize)
    {
        m_dimensions = std::make_unique<common::Vector2D>(width * unitSize, height * unitSize);
        m_position = std::make_unique<common::Vector2D>(x * unitSize, y * unitSize);
        m_unitSize = unitSize;
    }

    double Body::getAngle() const
    {
        return m_angle;
    }

    const common::Vector2D Body::getPosition() const
    {
        return *m_position;
    }

    const common::Vector2D Body::getDimensions() const
    {
        return *m_dimensions;
    }

    const common::Vector2D Body::getCenterPoint() const
    {
        return common::Vector2D((m_dimensions->x) / 2.0, (m_dimensions->y) / 2.0);
    }
}
}
