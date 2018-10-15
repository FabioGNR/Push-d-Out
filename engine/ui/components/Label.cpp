#include "Label.h"

namespace engine {
namespace ui {
    DrawContext Label::draw(DrawContext context)
    {
        common::Vector2D calculatedSize = calculateSize(context.availableSize);
        m_font.setPosition(context.pos + m_size.getPadding());
        m_font.setColor(Color(255, 255, 255, 255));
        context.renderer.draw(m_font);
        context.pos += calculatedSize;
        return context;
    }

    common::Vector2D Label::calculateSize(common::Vector2D availableSize) const
    {
        // add availableSize required for text
        common::Vector2D requiredSize = calculateTextSize();
        common::Vector2D size = m_size.getSize(requiredSize, availableSize);
        return size;
    }
}
}