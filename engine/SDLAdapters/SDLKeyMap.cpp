#include "SDLKeyMap.h"

IEvent* SDLKeyMap::getKeyValue(SDL_Event event, bool pressed)
{
    return new KeyEvent(keyCode[event.key.keysym.sym], pressed);
}