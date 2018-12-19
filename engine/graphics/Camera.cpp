#include "Camera.h"

namespace engine {
namespace graphics {
    common::Vector2D<int> Camera::translatePosition(common::Vector2D<double> position) const
    {
        // this method will return screen coordinates for a given world coordinate
        const auto viewStart = getViewStart();
        const auto relative = position - viewStart;
        auto viewport = (relative * getActualUnitSize()).castTo<int>();
        // flip Y because screen 0,0 is top left while game 0,0 is bottom left
        viewport.y = m_viewport.y - viewport.y;
        return viewport;
    }

    common::Vector2D<int> Camera::scaleSize(common::Vector2D<double> size) const
    {
        auto result = (size * getActualUnitSize());
        result.x = std::ceil(result.x);
        result.y = std::ceil(result.y);
        return result.castTo<int>();
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

    void Camera::setViewport(common::Vector2D<int> viewport)
    {
        m_viewport = viewport;
    }

    common::Vector2D<double> Camera::getViewStart() const
    {
        const common::Vector2D<double> offset = getVisibleRegionSize() / 2;
        return { m_position.x - offset.x, m_position.y - offset.y };
    }

    common::Vector2D<double> Camera::getVisibleRegionSize() const
    {
        return m_viewport.castTo<double>() / getActualUnitSize();
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
        bool xVisible = (end.x >= viewStart.x && position.x <= viewEnd.x);
        bool yVisible = (end.y >= viewStart.y && position.y <= viewEnd.y);
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

    double Camera::getFittedZoom(common::Vector2D<double> visibleDimensions) const
    {
        double idealPixelWidth = m_viewport.x / visibleDimensions.x;
        double idealHorizontalZoom = idealPixelWidth / m_unitSize;
        double idealPixelHeight = m_viewport.y / visibleDimensions.y;
        double idealVerticalZoom = idealPixelHeight / m_unitSize;
        return std::min(idealHorizontalZoom, idealVerticalZoom);
    }
}
}