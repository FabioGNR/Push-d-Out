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
        break;
    case SDL_KEYDOWN:
        break;
    default:
        return new UnknownEvent();
    }
}