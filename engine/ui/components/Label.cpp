#include "Label.h"

namespace engine {
namespace ui {
    DrawContext Label::draw(DrawContext context)
    {
        common::Vector2D<int> calculatedSize = calculateSize(context.renderer, context.availableSize);
        m_font.setPosition(context.pos + m_size.getPadding());
        m_font.setColor(m_color);
        context.renderer.draw(m_font);
        context.pos += calculatedSize;
        return context;
    }

    common::Vector2D<int> Label::calculateSize(const IRenderer& renderer, common::Vector2D<int> availableSize) const
    {
        // add availableSize required for text
        const auto requiredSize = calculateTextSize(renderer);
        const auto calculatedSize = m_size.getSize(requiredSize, availableSize);
        return calculatedSize;
    }
}
}