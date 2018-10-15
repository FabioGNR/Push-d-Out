#include "ComponentSize.h"

namespace engine {
namespace ui {
    common::Vector2D<int> ComponentSize::getSize(common::Vector2D<int> requiredSize,
        common::Vector2D<int> availableSize) const
    {
        // add padding for left,top and then right,bottom
        requiredSize += m_padding;
        requiredSize += m_padding;
        switch (m_typeX) {
        case ComponentSizeType::Stretch:
            requiredSize.x = static_cast<int>(availableSize.x * m_relativeRatio.x);
            break;
        case ComponentSizeType::Minimum:
            requiredSize.x = std::max(requiredSize.x, static_cast<int>(availableSize.x * m_relativeRatio.x));
            break;
        case ComponentSizeType::Fit:
        default:
            break;
        }
        switch (m_typeY) {
        case ComponentSizeType::Stretch:
            requiredSize.y = static_cast<int>(availableSize.y * m_relativeRatio.y);
            break;
        case ComponentSizeType::Minimum:
            requiredSize.y = std::max(requiredSize.y, static_cast<int>(availableSize.y * m_relativeRatio.y));
            break;
        case ComponentSizeType::Fit:
        default:
            break;
        }
        return requiredSize;
    }
}
}
