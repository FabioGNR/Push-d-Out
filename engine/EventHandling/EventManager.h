//
// Created by Richard on 26-9-2018.
//

#pragma once

#include "SDLAdapters/SDLEventAdapter.h"
#include "InputHandeling/InputManager.h"
#include <vector>

class EventManager {
private:
    InputManager im;
public:
    bool getEvents();
    InputManager* getInput();
};
