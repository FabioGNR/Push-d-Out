#include "Button.h"
#include <graphics/drawable/RectangleShape.h>

namespace engine {
namespace ui {

    DrawContext Button::draw(DrawContext context)
    {
        Color btnColor{
            255, 255, 255, 255
        };

        if (context.focusedComponent == this) {
            btnColor.r = 0;
        }
        common::Vector2D<int> calculatedSize = calculateSize(context.renderer, context.availableSize);
        RectangleShape shape{ context.pos, calculatedSize, btnColor };

        context.renderer.draw(shape);
        common::Vector2D<int> requiredTextSize = calculateTextSize(context.renderer);

        m_font.setPosition(context.pos + m_size.getPadding() + (calculatedSize - requiredTextSize) / 2);
        context.renderer.draw(m_font);
        context.pos += calculatedSize;
        return context;
    }

    common::Vector2D<int> Button::calculateSize(const IRenderer& renderer, common::Vector2D<int> availableSize) const
    {
        // add availableSize required for text
        const auto requiredSize = calculateTextSize(renderer);
        const auto calculatedSize = m_textPadding + m_size.getSize(requiredSize, availableSize);
        return calculatedSize;
    }

    void Button::processInputEvent(engine::input::maps::InputMap& inputMap)
    {
        //TODO: replace shouldExecute with proper mapping
        bool shouldExecute = inputMap.hasState(engine::input::Keys::SPACE, engine::input::States::PRESSED);
        shouldExecute = inputMap.hasState(engine::input::Keys::CON_A, engine::input::States::PRESSED) ? true : shouldExecute;
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