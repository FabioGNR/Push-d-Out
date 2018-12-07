#include "Image.h"
#include <common/Vector2D.h>

namespace engine {
namespace ui {
    DrawContext Image::draw(DrawContext context)
    {
        common::Vector2D<int> calculatedSize = calculateSize(context.renderer, context.availableSize);
        m_sprite.setSize(calculatedSize);
        m_sprite.setPosition(context.pos);
        context.renderer.draw(m_sprite);
        context.pos += calculatedSize;

        return context;
    }

    common::Vector2D<int> Image::calculateSize(const IRenderer& renderer, common::Vector2D<int> availableSize) const
    {
        const auto requiredSize = renderer.getSpriteSize(m_sprite);
        const auto calculatedSize = m_size.getSize(requiredSize, availableSize);
        return calculatedSize;
    }
}
}
