#pragma once

#include "WindowProperties.h"
#include "engine/common/Vector2D.h"

#include <utility>

namespace engine {
class Window {
public:
    explicit Window(WindowProperties properties)
        : m_properties{ std::move(properties) }
    {
    }
    Window(const Window& other) = default;
    Window& operator=(const Window& other) = default;

    Window(Window&& other) = default;
    Window& operator=(Window&& other) = default;
    virtual ~Window() = default;

    virtual const common::Vector2D<int> getDimensions() const = 0;

protected:
    WindowProperties m_properties;
};
}