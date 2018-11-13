#pragma once

#include "engine/common/Vector2D.h"
#include "engine/graphics/IRenderer.h"

#include <memory>
#include <utility>

namespace engine {
namespace ui {
    class Component;

    struct DrawContext {
        explicit DrawContext(common::Vector2D<int> _size, IRenderer& renderer, Component* focused)
            : pos{ 0, 0 }
            , availableSize{ _size }
            , renderer{ renderer }
            , focusedComponent{ focused }
        {
        }
        common::Vector2D<int> pos;
        common::Vector2D<int> availableSize;
        IRenderer& renderer;
        Component* focusedComponent;
    };
}
}