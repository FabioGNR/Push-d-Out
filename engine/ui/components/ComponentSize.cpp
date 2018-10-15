#include "ComponentSize.h"

namespace engine {
namespace ui {
    common::Vector2D ComponentSize::getSize(common::Vector2D requiredSize,
        common::Vector2D availableSize) const
    {
        // add padding for left,top and then right,bottom
        requiredSize += m_padding;
        requiredSize += m_padding;
        switch (m_typeX) {
        case ComponentSizeType::Stretch:
            requiredSize.x = availableSize.x * m_relativeRatio.x;
            break;
        case ComponentSizeType::Minimum:
            requiredSize.x = std::max(requiredSize.x, availableSize.x * m_relativeRatio.x);
            break;
        case ComponentSizeType::Fit:
        default:
            break;
        }
        switch (m_typeY) {
        case ComponentSizeType::Stretch:
            requiredSize.y = availableSize.y * m_relativeRatio.y;
            break;
        case ComponentSizeType::Minimum:
            requiredSize.y = std::max(requiredSize.y, availableSize.y * m_relativeRatio.y);
            break;
        case ComponentSizeType::Fit:
        default:
            break;
        }
        return requiredSize;
    }
}
}
