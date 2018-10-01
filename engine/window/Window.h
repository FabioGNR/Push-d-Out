#pragma once

#include <utility>
#include <common/Vector2D.h>
#include "WindowProperties.h"

namespace engine {
class Window {
public:
    explicit Window(WindowProperties properties)
        : m_properties{std::move(properties)}
    {
    }
    virtual ~Window() = default;

    virtual const common::Vector2D getDimensions() const = 0;

protected:
    WindowProperties m_properties;
};
}