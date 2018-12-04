#pragma once

#include <engine/events/models/IEvent.h>
#include <engine/input/Keys.h>
#include <map>

using SDL_Keycode = int;

namespace engine {
namespace input {
    struct SDLKeys {
        static const int conStart = 850;
        static const int mouseStart = 813;
        static const std::map<SDL_Keycode, Keys> KEYCODES;
        static input::Keys get(int SDL_Key);
    };
}
}