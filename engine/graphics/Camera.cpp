#include "Camera.h"
namespace engine {
namespace graphics {

    common::Vector2D<int> Camera::translatePosition(common::Vector2D<double> position) const
    {
        auto viewStart = getViewStart();
        auto relative = position - viewStart;
        return (relative * getActualUnitSize()).castTo<int>();
    }

    common::Vector2D<int> Camera::scaleSize(common::Vector2D<double> size) const
    {
        return (size * getActualUnitSize()).castTo<int>();
    }

    void Camera::setPosition(common::Vector2D<double> position)
    {
        m_position = position;
    }

    void Camera::setZoom(double zoomLevel)
    {
        m_zoomLevel = zoomLevel;
    }

    double Camera::getActualUnitSize() const
    {
        return m_unitSize * m_zoomLevel;
    }

    void Camera::setScreenSize(common::Vector2D<int> screenSize)
    {
        m_screenSize = screenSize;
    }

    common::Vector2D<double> Camera::getViewStart() const
    {
        common::Vector2D<double> center = m_position * getActualUnitSize();
        common::Vector2D<double> offset = getVisibleRegionSize() / 2;
        return center - offset;
    }

    common::Vector2D<double> Camera::getVisibleRegionSize() const
    {
        return m_screenSize.castTo<double>() / getActualUnitSize();
    }

    bool Camera::isPointVisible(common::Vector2D<double> position) const
    {
        auto viewStart = getViewStart();
        auto viewEnd = viewStart + getVisibleRegionSize();
        return position.x > viewStart.x && position.y > viewStart.y
            && position.x < viewEnd.x && position.y < viewEnd.y;
    }

    bool Camera::isRectangleVisible(common::Vector2D<double> position, common::Vector2D<double> size) const
    {
        auto viewStart = getViewStart();
        auto viewEnd = viewStart + getVisibleRegionSize();
        auto end = position + size;
        bool xVisible = (position.x > viewStart.x && position.x < viewEnd.x)
            || (end.x > viewStart.x && end.x < viewEnd.x);
        bool yVisible = (position.y > viewStart.y && position.y < viewEnd.y)
            || (end.y > viewStart.y && end.y < viewEnd.y);
        return xVisible && yVisible;
    }

    common::Vector2D<double> Camera::getPosition() const
    {
        return m_position;
    }
}
}