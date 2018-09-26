//
// Created by Richard on 26-9-2018.
//

#include "EventManager.h"

bool EventManager::getEvents()
{
    InputManager im;
    SDLEventAdapter ea;
    std::vector<IEvent*> test = ea.getEvents();
    for (IEvent* event : test) {
        if(event->store() == 'C'){
            im.storeInput(event);
        }
        event->printType();

        if (dynamic_cast<QuitEvent*>(event)) {
            return false;
        }
    }
    return true;
}