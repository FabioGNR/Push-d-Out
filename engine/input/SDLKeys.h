#pragma once

#include <SDL2/SDL.h>
#include <events/models/IEvent.h>
#include <input/Keys.h>
#include <map>

namespace engine {
namespace input {
    struct SDLKeys {
        static const std::map<SDL_Keycode, Keys> KEYCODES;
        static input::Keys get(SDL_Keycode keycode);
    };
}
}