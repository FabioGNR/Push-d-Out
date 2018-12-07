#include "SDLWindow.h"

#include <SDL.h>
#include <graphics/SDL/SDLRenderer.h>

namespace engine {

SDLWindow::SDLWindow(WindowProperties properties)
    : Window(std::move(properties))
    , m_window{ nullptr, nullptr }
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER);

    // creates a SDL_Window in a unique_ptr, specifying a custom delete function
    // namely the SDL_DestroyWindow function
    m_window
        = std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)>(
            SDL_CreateWindow(
                m_properties.title.c_str(),
                getPositionValue(m_properties.x),
                getPositionValue(m_properties.y),
                m_properties.width,
                m_properties.height,
                static_cast<Uint32>(getFlagsValue())),
            SDL_DestroyWindow);
}

SDLWindow::~SDLWindow()
{
    SDL_Quit();
}

int SDLWindow::getFlagsValue() const
{
    int flags = SDL_WINDOW_RESIZABLE;
    if (m_properties.fullscreen) {
        flags |= SDL_WINDOW_FULLSCREEN;
    }
    if (m_properties.maximized) {
        flags |= SDL_WINDOW_MAXIMIZED;
    }
    return flags;
}

int SDLWindow::getPositionValue(int coord) const
{
    if (m_properties.centered) {
        return static_cast<int>(SDL_WINDOWPOS_CENTERED);
    }
    return coord;
}

const common::Vector2D<int> SDLWindow::getDimensions() const
{
    common::Vector2D<int> screenSize{};
    SDL_GL_GetDrawableSize(m_window.get(), &screenSize.x, &screenSize.y);
    return screenSize;
}
}