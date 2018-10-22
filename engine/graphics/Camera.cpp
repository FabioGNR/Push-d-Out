#include "Camera.h"
namespace engine {
namespace graphics {
    common::Vector2D<int> Camera::translatePosition(common::Vector2D<double> position) const
    {
        // this method will return screen coordinates for a given world coordinate
        const auto viewStart = getViewStart();
        const auto relative = position - viewStart;
        auto screenPosition = (relative * getActualUnitSize()).castTo<int>();
        // flip Y because screen 0,0 is top left while game 0,0 is bottom left
        screenPosition.y = m_screenSize.y - screenPosition.y;
        return screenPosition;
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
        const common::Vector2D<double> offset = getVisibleRegionSize() / 2;
        return { m_position.x - offset.x, m_position.y - offset.y };
    }

    common::Vector2D<double> Camera::getVisibleRegionSize() const
    {
        return m_screenSize.castTo<double>() / getActualUnitSize();
    }

    bool Camera::isPointVisible(common::Vector2D<double> position) const
    {
        const auto viewStart = getViewStart();
        const auto viewEnd = viewStart + getVisibleRegionSize();
        return position.x >= viewStart.x && position.y >= viewStart.y
            && position.x <= viewEnd.x && position.y <= viewEnd.y;
    }

    bool Camera::isRectangleVisible(common::Vector2D<double> position, common::Vector2D<double> size) const
    {
        const auto viewStart = getViewStart();
        const auto viewEnd = viewStart + getVisibleRegionSize();
        const auto end = position + size;
        bool xVisible = (position.x >= viewStart.x && position.x <= viewEnd.x)
            || (end.x >= viewStart.x && end.x <= viewEnd.x);
        bool yVisible = (position.y >= viewStart.y && position.y <= viewEnd.y)
            || (end.y >= viewStart.y && end.y <= viewEnd.y);
        return xVisible && yVisible;
    }

    common::Vector2D<double> Camera::getPosition() const
    {
        return m_position;
    }

    double Camera::getZoom() const
    {
        return m_zoomLevel;
    }
}
}