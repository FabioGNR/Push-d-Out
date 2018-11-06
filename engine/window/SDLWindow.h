#pragma once
#include "Window.h"
#include <memory>

struct SDL_Window; // forward declaration to prevent SDL being included

namespace engine {
class SDLWindow : public Window {
public:
    explicit SDLWindow(WindowProperties properties);
    SDLWindow(const SDLWindow& other) = delete;
    SDLWindow& operator=(const SDLWindow& other) = delete;

    SDLWindow(SDLWindow&& other) = default;
    SDLWindow& operator=(SDLWindow&& other) = default;
    ~SDLWindow() override;

private:
    std::unique_ptr<SDL_Window, void (*)(SDL_Window*)> m_window;
    int getFlags() const;
    int getPosition(int coord) const;
    const common::Vector2D<int> getDimensions() const override;
    friend class SDLRenderer;
};
}