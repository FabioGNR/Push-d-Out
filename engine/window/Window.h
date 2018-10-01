#include <utility>

#pragma once
#include "WindowProperties.h"

namespace engine {
class Window {
public:
    explicit Window(WindowProperties properties)
        : m_properties{std::move(properties)}
    {
    }
    virtual ~Window() = default;

protected:
    WindowProperties m_properties;
};
}