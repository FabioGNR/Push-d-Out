#include "SDLKeyMap.h"

IEvent* SDLKeyMap::getKeyValue(SDL_Event event, bool pressed)
{

    //return new KeyEvent(keyCode[event.key.keysym.sym], pressed);

    switch (event.key.keysym.sym) {
    case SDLK_a:
        return new KeyEvent('A', pressed);
    case SDLK_b:
        return new KeyEvent('B', pressed);
    default:
        return new KeyEvent(event.key.keysym.sym, pressed);
    }
}