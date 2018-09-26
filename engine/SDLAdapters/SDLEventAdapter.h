//
// Created by Richard on 26-9-2018.
//
#pragma once

#include "EventHandling/Events/IEvent.h"
#include "EventHandling/Events/KeyEvent.h"
#include "EventHandling/Events/QuitEvent.h"
#include "EventHandling/Events/UnknownEvent.h"
#include "EventHandling/Events/WindowEvent.h"
#include <SDL2/SDL.h>
#include <vector>

class SDLEventAdapter {
private:
    IEvent* sortEvents(SDL_Event event);

public:
    std::vector<IEvent*> getEvents();
};
