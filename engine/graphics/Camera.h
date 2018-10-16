#pragma once
#include "common/Vector2D.h"

namespace engine {
namespace graphics {
    class Camera {
    public:
        Camera(int unitSize, common::Vector2D<int> screenSize)
            : m_screenSize{ screenSize }
            , m_zoomLevel{ 1 }
            , m_position{ 0, 0 }
            , m_unitSize{ unitSize }
        {
        }
        common::Vector2D<int> translatePosition(common::Vector2D<double> position) const;
        common::Vector2D<int> scaleSize(common::Vector2D<double> size) const;
        void setPosition(common::Vector2D<double> position);
        common::Vector2D<double> getPosition() const;
        void setZoom(double zoomLevel);
        void setScreenSize(common::Vector2D<int> screenSize);
        bool isPointVisible(common::Vector2D<double> position) const;
        bool isRectangleVisible(common::Vector2D<double> position, common::Vector2D<double> size) const;

    private:
        common::Vector2D<int> m_screenSize;
        double m_zoomLevel;
        common::Vector2D<double> m_position;
        int m_unitSize = 16;
        double getActualUnitSize() const;
        common::Vector2D<double> getViewStart() const;
        common::Vector2D<double> getVisibleRegionSize() const;
    };
}
}