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
    Body::Body(common::Vector2D<double> position, common::Vector2D<double> dimension, World& world)
        : m_position{ position }
        , m_dimensions{ dimension }
        , m_world{ world }
    {
    }

    Body::~Body() = default;

    double Body::getAngle() const
    {
        return m_angle;
    }

    const common::Vector2D<double> Body::getPosition() const
    {
        // because box2d sees its position as center, shift it by half of the dimensions
        return { m_position.x - m_dimensions.x / 2,
            m_position.y - m_dimensions.y / 2 };
    }

    void Body::setPosition(const common::Vector2D<double> position)
    {
        m_position = position;
    }

    const common::Vector2D<double> Body::getDimensions() const
    {
        return m_dimensions;
    }

    const common::Vector2D<double> Body::getCenterPoint() const
    {
        return common::Vector2D<double>((m_dimensions.x) / 2.0, (m_dimensions.y) / 2.0);
    }

    void Body::setEntityId(ecs::EntityId id)
    {
        m_body->SetUserData((void*)id);
    }

    ecs::EntityId Body::getEntityId()
    {
        return (ecs::EntityId)m_body->GetUserData();
    }
}
}
