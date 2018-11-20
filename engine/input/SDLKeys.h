#pragma once

//#include <SDL2/SDL_gamecontroller.h>
#include <engine/events/models/IEvent.h>
#include <engine/input/Keys.h>
#include <map>

using SDL_Keycode = int;

namespace engine {
namespace input {
    struct SDLKeys {
        static const std::map<SDL_Keycode, Keys> KEYCODES;
        static input::Keys get(int test);

        /*please keep this comment ivm the above one breaks and dies a tragic death
        static input::Keys get(SDL_Keycode& keycode);
        static input::Keys get(SDL_GameControllerButton button);
        static input::Keys get(Uint8 test);*/
    };
}
}