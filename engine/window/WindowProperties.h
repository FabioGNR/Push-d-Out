#pragma once
#include <string>

namespace engine {
struct WindowProperties {
    std::string title;
    bool fullscreen;
    bool maximized;
    bool centered;
    int width;
    int height;
    int x;
    int y;
};
}