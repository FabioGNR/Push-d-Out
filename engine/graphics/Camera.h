#pragma once
#include "engine/common/Vector2D.h"

namespace engine {
namespace graphics {
    class Camera {
        common::Vector2D<int> m_viewport;
        double m_zoomLevel;
        common::Vector2D<double> m_position;
        int m_unitSize = 16;

    public:
        Camera(int unitSize, common::Vector2D<int> viewport)
            : m_viewport{ viewport }
            , m_position{ 0, 0 }
            , m_unitSize{ unitSize }
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

    private:

        double getActualUnitSize() const;

        common::Vector2D<double> getViewStart() const;

        common::Vector2D<double> getVisibleRegionSize() const;
    };
}
}