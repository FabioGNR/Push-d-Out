#pragma once

#include <engine/events/models/IEvent.h>
#include <engine/input/Keys.h>
#include <map>
#include <SDL2/SDL_gamecontroller.h>

using SDL_Keycode = int;

namespace engine {
namespace input {
    struct SDLKeys {
        static const std::map<SDL_Keycode, Keys> KEYCODES;
        static input::Keys get(SDL_Keycode& keycode);
        static input::Keys get(SDL_GameControllerButton button);
    };
}
}