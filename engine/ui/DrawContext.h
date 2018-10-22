#include <utility>

#pragma once
#include "common/Vector2D.h"
#include "graphics/IRenderer.h"
#include <memory>

namespace engine {
namespace ui {
    class Component;

    struct DrawContext {
        explicit DrawContext(common::Vector2D<int> _size, IRenderer& renderer, std::shared_ptr<Component> focused)
            : pos{ 0, 0 }
            , availableSize{ _size }
            , renderer{ renderer }
            , focusedComponent{ std::move(focused) }
        {
        }
        common::Vector2D<int> pos;
        common::Vector2D<int> availableSize;
        IRenderer& renderer;
        std::shared_ptr<Component> focusedComponent;
    };
}
}