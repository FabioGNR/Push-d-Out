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
        event->printType();
        if (dynamic_cast<IControlEvent*>(event)) {
            im.storeInput((IControlEvent*)event);
        } else if (dynamic_cast<QuitEvent*>(event)) { // TODO eventually delete this
            return false;
        } else if (dynamic_cast<IOtherEvent*>(event)) {
            // do nothing
        }
    }
    return true;
}