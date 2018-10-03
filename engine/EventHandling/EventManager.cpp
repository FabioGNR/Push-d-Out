//
// Created by Richard on 26-9-2018.
//

#include "EventManager.h"

bool EventManager::getEvents()
{
    InputManager im;
    SDLEventAdapter ea;
    std::vector<IEvent*> test = ea.getEvents();

    std::vector<IEvent*> controlEvents;
    std::vector<IEvent*> otherEvents;

    for (IEvent* event : test) {
        event->store(&controlEvents, &otherEvents);

        if (dynamic_cast<QuitEvent*>(event)) {
            return false;
        }

        event->printType();
    }
    //im.storeInput(controlEvents); TODO this
    return true;
}