#include <utility>

#pragma once
#include "UIRenderer.h"
#include "common/Vector2D.h"

namespace engine {
namespace ui {
    class Component;

    struct DrawContext {
        explicit DrawContext(common::Vector2D<int> _size, UIRenderer renderer, std::shared_ptr<Component> focused)
            : pos{ 0, 0 }
            , availableSize{ _size }
            , renderer{ renderer }
            , focusedComponent{ std::move(focused) }
        {
        }
        common::Vector2D<int> pos;
        common::Vector2D<int> availableSize;
        UIRenderer renderer;
        std::shared_ptr<Component> focusedComponent;
    };
}
}