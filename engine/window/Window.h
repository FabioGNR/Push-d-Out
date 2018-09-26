#pragma once
#include "WindowProperties.h"

namespace engine {
class Window {
public:
    Window(WindowProperties properties)
        : m_properties{ properties }
    {
    }
    virtual ~Window() = default;

protected:
    WindowProperties m_properties;
};
}