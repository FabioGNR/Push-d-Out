//
// Created by Richard on 26-9-2018.
//

#include "SDLEventAdapter.h"

std::vector<IEvent*> SDLEventAdapter::getEvents()
{
    std::vector<IEvent*> events;
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        events.push_back(sortEvents(event));
    }
    return events;
}

IEvent* SDLEventAdapter::sortEvents(SDL_Event event)
{
    switch (event.type) {
    case SDL_QUIT:
        return new QuitEvent();
    case SDL_KEYUP:
        return new KeyEvent(getKeyValue(event), true);
    case SDL_KEYDOWN:
        return new KeyEvent(getKeyValue(event), false);
    default:
        return new UnknownEvent();
    }
}

char SDLEventAdapter::getKeyValue(SDL_Event event)
{
    switch (event.key.keysym.sym) {
    case SDLK_a:
        return 'A';
    case SDLK_b:
        return 'B';
    default:
        return 0;
    }
}