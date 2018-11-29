#pragma once
#include "ComponentSize.h"
#include "engine/common/Vector2D.h"
#include "engine/ui/DrawContext.h"
#include <engine/common/Vector2D.h>
#include <engine/input/maps/AnalogMap.h>
#include <engine/ui/DrawContext.h>

#include <memory>

namespace engine {
namespace ui {
    class Component {
    public:
        explicit Component(ComponentSize size)
            : m_size{ size }
        {
        }
        virtual ~Component() = default;

        virtual DrawContext draw(DrawContext context) = 0;

        virtual void processInputEvent(engine::input::maps::AnalogMap& /*unused*/) {}
        virtual common::Vector2D<int> calculateSize(const IRenderer& renderer, common::Vector2D<int> availableSize) const = 0;
        ComponentSize getSize() { return m_size; }
        virtual bool isNavigatable() { return false; }

    protected:
        ComponentSize m_size;
    };
}
}