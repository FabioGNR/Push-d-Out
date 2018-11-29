#pragma once

#include "engine/common/Vector2D.h"

namespace engine {
namespace graphics {
    class Camera {
    public:
        Camera(int unitSize, common::Vector2D<int> viewport)
            : m_viewport{ viewport }
            , m_zoomLevel{ 1 }
            , m_position{ 0, 0 }
            , m_unitSize{ unitSize }
        {
        }

        Camera()
            : m_viewport{ 1, 1 }
            , m_zoomLevel{ 1 }
            , m_position{ 0, 0 }
            , m_unitSize{ 1 }
        {
        }

        common::Vector2D<int> translatePosition(common::Vector2D<double> position) const;

        common::Vector2D<int> scaleSize(common::Vector2D<double> size) const;

        void setPosition(common::Vector2D<double> position);

        common::Vector2D<double> getPosition() const;

        void setZoom(double zoomLevel);

        double getZoom() const;

        void setViewport(common::Vector2D<int> viewport);

        bool isPointVisible(common::Vector2D<double> position) const;

        bool isRectangleVisible(common::Vector2D<double> position, common::Vector2D<double> size) const;

        double getFittedZoom(common::Vector2D<double> visibleDimensions) const;

        common::Vector2D<double> getVisibleRegionSize() const;

    private:
        common::Vector2D<int> m_viewport;
        double m_zoomLevel;
        common::Vector2D<double> m_position;
        int m_unitSize = 16;

        double getActualUnitSize() const;

        common::Vector2D<double> getViewStart() const;
    };
}
}