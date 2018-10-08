#pragma once

#include "EventHandling/Events/IEvent.h"
#include "EventHandling/Events/KeyEvent.h"
#include <SDL2/SDL.h>
#include <map>

class SDLKeyMap {
private:
    enum keys {
        A,
        B,
        C,
        D,
        E,
        F,
        G,
        H,
        I,
        J,
        K,
        L,
        M,
        N,
        O,
        P,
        Q,
        R,
        S,
        T,
        U,
        V,
        W,
        X,
        Y,
        Z
    };
    std::map<SDL_Keycode, keys> keyCode = {
        { SDLK_a, keys::A },
        { SDLK_b, keys::B }
    };

public:
    IEvent* getKeyValue(SDL_Event event, bool pressed);
};
