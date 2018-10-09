#include "Button.h"
#include <graphics/drawable/RectangleShape.h>

namespace engine {
namespace ui {

    DrawContext Button::draw(DrawContext context)
    {
        Color btnColor;
        btnColor.r = btnColor.g = btnColor.b = 255;
        btnColor.a = 130;
        if (context.focusedComponent.get() == this) {
            btnColor.r = 0;
        }
        common::Vector2D calculatedSize = calculateSize(context.availableSize);
        RectangleShape shape{ context.pos, calculatedSize, btnColor };

        context.renderer.draw(shape);
        m_font.setPosition(context.pos + m_size.getPadding());
        context.renderer.draw(m_font);
        context.pos += calculatedSize;
        return context;
    }

    common::Vector2D Button::calculateSize(common::Vector2D availableSize) const
    {
        // add availableSize required for text
        common::Vector2D requiredSize = calculateTextSize();
        common::Vector2D size = m_size.getSize(requiredSize, availableSize);
        return size;
    }

    void Button::processInputEvent()
    {
        if (m_action != nullptr) {
            m_action->execute();
        }
    }

    bool Button::isNavigatable()
    {
        return true;
    }
}
}