//
// Created by Richard on 26-9-2018.
//
#pragma once

#include "EventHandling/Events/IEvent.h"
#include "EventHandling/Events/KeyEvent.h"
#include "EventHandling/Events/QuitEvent.h"
#include "EventHandling/Events/UnknownEvent.h"
#include <SDL2/SDL.h>
#include <map>
#include <vector>

class SDLEventAdapter {
private:
    std::map<SDL_Keycode, char> KeyCode;
    IEvent* sortEvents(SDL_Event event);
    char getKeyValue(SDL_Event event);

public:
    std::vector<IEvent*> getEvents();
};
