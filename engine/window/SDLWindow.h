#pragma once
#include "Window.h"
#include <memory>

struct SDL_Window; // forward declaration to prevent SDL being included

namespace engine {
class SDLWindow : public Window {
public:
    SDLWindow(WindowProperties properties);
    ~SDLWindow() override;

private:
    std::unique_ptr<SDL_Window, void (*)(SDL_Window*)> m_window;
    int getFlags() const;
    int getPosition(const int coord) const;
};
}