#include "Button.h"
#include <graphics/drawable/RectangleShape.h>
#include <input/maps/KeyMap.h>

namespace engine {
namespace ui {

    DrawContext Button::draw(DrawContext context)
    {
        Color btnColor{
            255, 255, 255, 130
        };

        if (context.focusedComponent.get() == this) {
            btnColor.r = 0;
        }
        common::Vector2D<int> calculatedSize = calculateSize(context.renderer, context.availableSize);
        RectangleShape shape{ context.pos, calculatedSize, btnColor };

        context.renderer.draw(shape);
        m_font.setPosition(context.pos + m_size.getPadding());
        context.renderer.draw(m_font);
        context.pos += calculatedSize;
        return context;
    }

    common::Vector2D<int> Button::calculateSize(const IRenderer& renderer, common::Vector2D<int> availableSize) const
    {
        // add availableSize required for text
        common::Vector2D<int> requiredSize = calculateTextSize(renderer);
        common::Vector2D<int> size = m_size.getSize(requiredSize, availableSize);
        return size;
    }

    void Button::processInputEvent(engine::input::ControllerMap& keyMap)
    {
        //TODO: replace shouldExecute with proper mapping
        bool shouldExecute = keyMap.hasKeyState(engine::input::Keys::SPACE, engine::input::KeyStates::PRESSED);
        if (shouldExecute && m_action != nullptr) {
            m_action->execute();
        }
    }

    bool Button::isNavigatable()
    {
        return true;
    }
}
}